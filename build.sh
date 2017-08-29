#!/bin/bash

export LD_LIBRARY_PATH=/home/carlos/dev/graphics/libcxx/libcxx/build/lib:/home/carlos/dev/graphics/libcxx/libcxxabi/build/lib:$LD_LIBRARY_PATH

rm -rf build
mkdir build && cd build
cmake ..                                                                                \
    -DCMAKE_BUILD_TYPE=Debug                                                            \
    -DCMAKE_CXX_COMPILER=clang++                                                        \
    -DCMAKE_C_COMPILER=clang                                                            \
    -DCMAKE_LIBCXXABI_INCLUDE_PATH=/home/carlos/dev/graphics/libcxx/libcxxabi/include   \
    -DCMAKE_LIBCXXABI_LIB_PATH=/home/carlos/dev/graphics/libcxx/libcxxabi/build/lib     \
    -DCMAKE_LIBCXX_INCLUDE_PATH=/home/carlos/dev/graphics/libcxx/libcxx/include         \
    -DCMAKE_LIBCXX_LIB_PATH=/home/carlos/dev/graphics/libcxx/libcxx/build/lib
make -j4    
