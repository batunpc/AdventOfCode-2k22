#!/bin/bash

set -e

hr() {
    if
        command -v lolcat >/dev/null 2>&1
    then
        echo "🎄==========================🎄" | lolcat
    else
        echo "🎄==========================🎄"
    fi
    echo
}

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

cmake -S .. -B . -G Ninja >/dev/null &&
    cmake --build . --target "$1" -- -j 4 || exit 1

hr

directory=$1                                    # Day <dirname>
number=$(echo "$directory" | grep -o '[0-9]\+') # extract number from <dirname>

cd "$OLDPWD/$BUILD_DIR/Day$number" && ./"$1" || exit 1 # use as the executable name
