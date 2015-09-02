cmake_minimum_required(VERSION 3.2.2)
project(SceneR_Root)
enable_language(CXX)

#set(CMAKE_C_COMPILER /usr/bin/clang)
#set(CMAKE_CXX_COMPILER /usr/bin/clang++)

# enable c++11 & clang standard library
# set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -stdlib=libc++ -g3 -Wall -O0")

# Project subdirectories
subdirs(SceneR SceneR.Framework SceneR.Framework.Tests)
