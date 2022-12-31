#!/bin/bash

if [ -d build ]; then
    rm -rf build
fi

mkdir build && cd build

#!/bin/bash

if [[ -z $1 ]]; then
    echo "Usage: $0 day name <target>"
    exit 1
fi

cmake -S .. -B . && cmake --build . --target $1

if [ $? -eq 0 ]; then
    cd $OLDPWD/build/$1 && make && ./$1
else
    echo "Build failed."
    exit 1
fi
