[![Build Status][ci-img]][ci] [![Coverage Status][cov-img]][cov] [![OpenTracing 1.0 Enabled][ot-img]][ot-url]

# jaeger-client-cpp
C++ OpenTracing binding for Jaeger

## Contributing

Please see [CONTRIBUTING.md](CONTRIBUTING.md).

## Generated files

This project uses Apache Thrift for wire-format protocol support code
generation. It currently requires exactly Thrift 0.9.2 or 0.9.3. Patches have
been applied to the generated code so it cannot be directly re-generated from
the IDL in the `idl` submodule

(see https://github.com/jaegertracing/jaeger-client-cpp/issues/45)

The code can be re-generated with

    git submodule init
    git submodule update
    find idl/thrift/ -type f -name \*.thrift -exec thrift -gen cpp -out src/jaegertracing/thrift-gen {} \;

but at time of writing (Thrift 0.11.0) the resulting code is invalid due to
https://issues.apache.org/jira/browse/THRIFT-4484.

## Use from C

Care is required:

* All functions called from C must be `extern "C"` linkage
* No exceptions may be thrown into C code (assuming standard C)
* Memory allocated in C++ must be `delete`d appropriately not `free()`d
* Memory allocated in C must be `free`d appropriately not `delete`d

but it works well. See `src/cdemo`.

The general idea is to expose a set of C functions as thunks for your tracing
and to expose facilities like exporting and importing trace context data. Then
use only those functions from C, passing around any C++ objects you need as
opaque pointers.

## License

[Apache 2.0 License](./LICENSE).

[ci-img]: https://travis-ci.org/jaegertracing/jaeger-client-cpp.svg?branch=master
[ci]: https://travis-ci.org/jaegertracing/jaeger-client-cpp
[cov-img]: https://codecov.io/gh/jaegertracing/jaeger-client-cpp/branch/master/graph/badge.svg
[cov]: https://codecov.io/gh/jaegertracing/jaeger-client-cpp
[ot-img]: https://img.shields.io/badge/OpenTracing--1.0-enabled-blue.svg
[ot-url]: http://opentracing.io

