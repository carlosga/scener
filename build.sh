#!/bin/bash

rm -rf build
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug
make -j4    
strace ./Debug/vulkan-sample
