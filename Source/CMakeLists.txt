cmake_minimum_required(VERSION 3.2.2)
enable_language(CXX)

# enable c++14 & clang standard library
set (CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++14 -stdlib=libc++ -g3 -O0 -Wall -Wextra -Wno-unused-parameter")

# -Weverything -Wno-reserved-id-macro -Wno-shadow -Wno-c++98-compat -Wno-padded -Wno-unused-parameter -Wno-nested-anon-types -Wno-gnu-anonymous-struct

# SceneR Framework
set (SCENER_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/SceneR)
set (SCENER_LIB_DIRS     ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE})
set (SCENER_LIBRARIES    SceneR)

# Project subdirectories
add_subdirectory(SceneR)

# Tests subdirectories
add_subdirectory(Tests)

# Samples subdirectories
# add_subdirectory(Samples)
