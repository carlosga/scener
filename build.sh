#!/bin/bash

clear && rm -rf build && mkdir build && cd build

# gcc (debug)
cmake .. -DCMAKE_BUILD_TYPE=Debug

# clang (Debug)
# cmake .. -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_C_COMPILER=clang

make -j
# strace ./build/Debug/vulkan-sample
