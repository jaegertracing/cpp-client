#!/bin/bash

# Based on https://github.com/codecov/example-cpp11-cmake/blob/master/run_build.sh.

set -e

RED='\033[0;31m'
BLUE='\033[0;34m'
NO_COLOR='\033[0m'
GREEN='\033[0;32m'

function info() {
    echo -e "${GREEN}$1${NO_COLOR}"
}

function working() {
    echo -e "${BLUE}$1${NO_COLOR}"
}

function main() {
    mkdir -p build
    cd build
    coverage_option=${COVERAGE:+"-DJAEGERTRACING_COVERAGE=ON"}
    cmake -DCMAKE_BUILD_TYPE=Debug -DBUILD_SHARED_LIBS=ON "${coverage_option}" ..
    make -j3 UnitTest DynamicallyLoadTracerTest
    info "Running tests..."
    ctest -V
    working "All tests compiled and passed"
}

main
