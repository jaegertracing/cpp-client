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

#include "jaegertracing/Span.h"

#include "jaegertracing/Tracer.h"

namespace jaegertracing {

void Span::SetBaggageItem(opentracing::string_view restrictedKey,
                          opentracing::string_view value) noexcept
{
    std::lock_guard<std::mutex> lock(_mutex);
    std::shared_ptr<const Tracer> tracer(_tracer.lock());
    const auto& baggageSetter = tracer->baggageSetter();
    auto baggage = _context.baggage();
    baggageSetter.setBaggage(*this,
                             baggage,
                             restrictedKey,
                             value,
                             [this](std::vector<Tag>::const_iterator first,
                                    std::vector<Tag>::const_iterator last) {
                                 logFieldsNoLocking(first, last);
                             });
    _context = _context.withBaggage(baggage);
}

void Span::FinishWithOptions(
    const opentracing::FinishSpanOptions& finishSpanOptions) noexcept
{
    std::shared_ptr<const Tracer> tracer;
    {
        std::lock_guard<std::mutex> lock(_mutex);
        if (_context.isSampled()) {
            _duration = finishSpanOptions.finish_steady_timestamp - _startTime;
        }
        tracer = _tracer.lock();
    }

    // Call `reportSpan` even for non-sampled traces.
    if (tracer) {
        tracer->reportSpan(*this);
    }
}

const opentracing::Tracer& Span::tracer() const noexcept
{
    std::lock_guard<std::mutex> lock(_mutex);
    std::shared_ptr<const opentracing::Tracer> tracer(_tracer.lock());
    if (tracer) {
        return *tracer;
    }
    tracer = opentracing::Tracer::Global();
    assert(tracer);
    return *tracer;
}

std::string Span::serviceName() const noexcept
{
    std::lock_guard<std::mutex> lock(_mutex);
    return serviceNameNoLock();
}

std::string Span::serviceNameNoLock() const noexcept
{
    std::shared_ptr<const Tracer> tracer(_tracer.lock());
    if (!tracer) {
        return std::string();
    }
    return tracer->serviceName();
}

}  // namespace jaegertracing
