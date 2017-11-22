/*
 * Copyright (c) 2017 Uber Technologies, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "jaegertracing/Tracer.h"

#include "jaegertracing/Reference.h"

namespace jaegertracing {

using StrMap = SpanContext::StrMap;

constexpr int Tracer::kGen128BitOption;

std::unique_ptr<opentracing::Span>
Tracer::StartSpanWithOptions(string_view operationName,
                             const opentracing::StartSpanOptions& options) const
    noexcept
{
    try {
        const auto result = analyzeReferences(options.references);
        const auto* parent = result._parent;
        const auto& references = result._references;

        std::vector<Tag> samplerTags;
        auto newTrace = false;
        SpanContext ctx;
        if (!parent || !parent->isValid()) {
            newTrace = true;
            auto highID = static_cast<uint64_t>(0);
            if (_options & kGen128BitOption) {
                highID = randomID();
            }
            const TraceID traceID(highID, randomID());
            const auto spanID = traceID.low();
            const auto parentID = 0;
            auto flags = static_cast<unsigned char>(0);
            if (parent && parent->isDebugIDContainerOnly()) {
                flags |=
                    (static_cast<unsigned char>(SpanContext::Flag::kSampled) |
                     static_cast<unsigned char>(SpanContext::Flag::kDebug));
            }
            else {
                const auto samplingStatus =
                    _sampler->isSampled(traceID, operationName);
                if (samplingStatus.isSampled()) {
                    flags |=
                        static_cast<unsigned char>(SpanContext::Flag::kSampled);
                    samplerTags = samplingStatus.tags();
                }
            }
            ctx = SpanContext(traceID, spanID, parentID, flags, StrMap());
        }
        else {
            const auto traceID = parent->traceID();
            const auto spanID = randomID();
            const auto parentID = parent->spanID();
            const auto flags = parent->flags();
            ctx = SpanContext(traceID, spanID, parentID, flags, StrMap());
        }

        if (parent && !parent->baggage().empty()) {
            ctx = ctx.withBaggage(parent->baggage());
        }

        return startSpanInternal(ctx,
                                 operationName,
                                 options.start_system_timestamp,
                                 options.start_steady_timestamp,
                                 samplerTags,
                                 options.tags,
                                 newTrace,
                                 references);
    } catch (...) {
        utils::ErrorUtil::logError(
            *_logger, "Error occurred in Tracer::StartSpanWithOptions");
        return nullptr;
    }
}

std::unique_ptr<Span>
Tracer::startSpanInternal(const SpanContext& context,
                          const std::string& operationName,
                          const SystemClock::time_point& startTimeSystem,
                          const SteadyClock::time_point& startTimeSteady,
                          const std::vector<Tag>& internalTags,
                          const std::vector<OpenTracingTag>& tags,
                          bool newTrace,
                          const std::vector<Reference>& references) const
{
    std::vector<Tag> spanTags;
    spanTags.reserve(tags.size() + internalTags.size());
    std::transform(
        std::begin(tags),
        std::end(tags),
        std::back_inserter(spanTags),
        [](const OpenTracingTag& tag) { return Tag(tag.first, tag.second); });
    spanTags.insert(
        std::end(spanTags), std::begin(internalTags), std::end(internalTags));

    std::unique_ptr<Span> span(new Span(shared_from_this(),
                                        context,
                                        operationName,
                                        startTimeSystem,
                                        startTimeSteady,
                                        spanTags,
                                        references));

    _metrics->spansStarted().inc(1);
    if (span->context().isSampled()) {
        _metrics->spansSampled().inc(1);
        if (newTrace) {
            _metrics->tracesStartedSampled().inc(1);
        }
    }
    else {
        _metrics->spansNotSampled().inc(1);
        if (newTrace) {
            _metrics->tracesStartedNotSampled().inc(1);
        }
    }

    return span;
}

Tracer::AnalyzedReferences
Tracer::analyzeReferences(const std::vector<OpenTracingRef>& references) const
{
    AnalyzedReferences result;
    auto hasParent = false;
    const auto* parent = result._parent;
    for (auto&& ref : references) {
        const auto* ctx = dynamic_cast<const SpanContext*>(ref.second);

        if (!ctx) {
            _logger->error("Reference contains invalid type of SpanReference");
            continue;
        }

        if (!ctx->isValid() && !ctx->isDebugIDContainerOnly() &&
            ctx->baggage().empty()) {
            continue;
        }

        result._references.emplace_back(Reference(*ctx, ref.first));

        if (!hasParent) {
            parent = ctx;
            hasParent =
                (ref.first == opentracing::SpanReferenceType::ChildOfRef);
        }
    }

    if (!hasParent && parent && parent->isValid()) {
        // Use `FollowsFromRef` in place of `ChildOfRef`.
        hasParent = true;
    }

    if (hasParent) {
        assert(parent);
        result._parent = parent;
    }

    return result;
}

}  // namespace jaegertracing
