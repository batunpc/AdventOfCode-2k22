#!/bin/bash

hr() {
    echo "+=============+" | lolcat
}

if [ -d build ]; then
    rm -rf build
fi

mkdir build && cd build

if [[ -z $1 ]]; then
    echo "Usage: $0 day name <target>"
    exit 1
fi

cmake -S .. -B . && cmake --build . --target $1

if [ $? -eq 0 ]; then
    hr
    echo "Running $1"
    hr
    cd $OLDPWD/build/$1 && ./$1
else
    echo "Build failed."
    exit 1
fi
