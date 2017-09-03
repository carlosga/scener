#!/bin/bash

export LD_LIBRARY_PATH=/home/carlos/dev/graphics/libcxx/libcxx/build/lib:/home/carlos/dev/graphics/libcxx/libcxxabi/build/lib:$LD_LIBRARY_PATH

rm -rf build
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug
make -j4    
