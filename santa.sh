#!/bin/bash

# Exit immediately if any command returns a non-zero exit code
set -e

hr() {
    echo "+=============+" | lolcat
}

# Define variables for file and directory paths
BUILD_DIR=build

if [ -d "$BUILD_DIR" ]; then
    rm -rf "$BUILD_DIR" && mkdir "$BUILD_DIR" || exit 1
else
    mkdir "$BUILD_DIR" || exit 1
fi

cd "$BUILD_DIR" || exit 1

if [[ -z $1 ]]; then
    echo "Usage: $0 day name <target>"
    exit 1
fi

cmake -S .. -B . -G Ninja && ninja -t color && cmake --build . --target "$1" -- -j 4 || exit 1

hr
cd "$OLDPWD/$BUILD_DIR/$1" && ./"$1" || exit 1
