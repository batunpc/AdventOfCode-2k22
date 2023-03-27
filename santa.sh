#!/bin/bash

set -euo pipefail

print_banner() {
    local banner_text="🎄==========================🎄"
    if command -v lolcat >/dev/null 2>&1; then
        echo "$banner_text" | lolcat
    else
        echo "$banner_text"
    fi
}

build_project() {
    local build_dir="$1"
    local day_name="$2"
    local target="$3"
    local num_cores="$4"
    local build_type="$5"

    if [[ ! -d "$build_dir" ]]; then
        mkdir "$build_dir" || {
            echo "Error: Failed to create build directory"
            exit 1
        }
    fi

    cd "$build_dir" || {
        echo "Error: Failed to change directory to $build_dir"
        exit 1
    }

    cmake_args=(
        -S ..
        -B .
        -G Ninja
    )

    if [[ -n "$build_type" ]]; then
        cmake_args+=("-DCMAKE_BUILD_TYPE=$build_type")
    fi

    cmake "${cmake_args[@]}" >/dev/null || {
        echo "Error: Failed to configure project"
        exit 1
    }

    cmake --build . --target "$target" -- -j "$num_cores" || {
        echo "Error: Failed to build project"
        exit 1
    }

    print_banner

    executable="./${day_name}/${target}"
    if [[ ! -x "$executable" ]]; then
        echo "Error: $executable is not executable"
        exit 1
    fi

    "$executable" || {
        echo "Error: Failed to run $executable"
        exit 1
    }
}

usage() {
    echo "Usage: $(basename "$0") day_name target [options]"
    echo "Options:"
    echo "  -j NUM_CORES  Use NUM_CORES cores for building the project (default: 4)"
    echo "  --release     Build and run the executable in release mode"
}

# Default values
num_cores=4
build_type=""

while [[ $# -gt 0 ]]; do
    case "$1" in
    -j)
        num_cores="$2"
        shift 2
        ;;
    --release)
        build_type="Release"
        shift
        ;;
    *)
        break
        ;;
    esac
done

if [[ $# -lt 2 ]]; then
    usage
    exit 1
fi

day_name="$1"
target="$2"

if ! [[ "$day_name" =~ ^Day[0-9]+$ ]]; then
    echo "Error: day_name must be in the format 'Day<number>'"
    exit 1
fi

build_dir="build/${day_name}"
build_project "$build_dir" "$day_name" "$target" "$num_cores" "$build_type"
