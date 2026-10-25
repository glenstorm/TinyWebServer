#!/bin/sh
set -eu

cd "$(dirname "$0")"

if ! command -v g++ >/dev/null 2>&1; then
    echo "g++ was not found. In WSL run: sudo apt install build-essential cmake pkg-config libmysqlclient-dev" >&2
    exit 1
fi

build_type="${CMAKE_BUILD_TYPE:-Debug}"
cmake -S . -B build -DCMAKE_BUILD_TYPE="${build_type}" -DCMAKE_CXX_COMPILER=g++
cmake --build build --target server -j"$(nproc)"

echo "Built ./build/server ($(g++ --version | head -1))"
