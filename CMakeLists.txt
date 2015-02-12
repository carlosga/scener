cmake_minimum_required(VERSION 2.8.4)
project(SceneR.Root)
enable_language(CXX)

## set(CMAKE_C_COMPILER clang-3.5)
## set(CMAKE_CXX_COMPILER clang++-3.5)

# enable c++11 & clang standard library
## set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -stdlib=libc++ -g3 -Wall -O0")

# Project subdirectories
subdirs(SceneR SceneR.Framework SceneR.Framework.Tests)
