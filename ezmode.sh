# check if build directory exists if it does delete it and create again

if [ -d build ]; then
    rm -rf build
fi

# take the target as an argument and build it
mkdir build && cd build && cmake -S .. -B . && cmake --build . --target $1
