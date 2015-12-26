cmake_minimum_required(VERSION 3.2.2)
project(SceneR_Root)
enable_language(CXX)

# enable c++14 & clang standard library
set (CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++14 -stdlib=libc++ -g3 -O0 -Wall -Wextra -Wno-unused-parameter")
# -Weverything -Wno-reserved-id-macro -Wno-shadow -Wno-c++98-compat -Wno-padded -Wno-unused-parameter -Wno-nested-anon-types -Wno-gnu-anonymous-struct

# External dependencies
#
# Base directory
set (EXTERNALS_BASE_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/externals)
# JSON11
set (JSON11_INCLUDE_DIRS ${EXTERNALS_BASE_DIR}/json11)
set (JSON11_SOURCE_DIRS  ${EXTERNALS_BASE_DIR}/json11)
# Microsoft/GSL
set (GSL_INCLUDE_DIRS    ${EXTERNALS_BASE_DIR}/gsl/include)

# Google Test configuration
set (GOOGLE_TEST_BASE_DIR      ${CMAKE_CURRENT_SOURCE_DIR}/../gtest-1.7.0)
set (GOOGLE_TEST_INCLUDE_DIRS  ${GOOGLE_TEST_BASE_DIR}/include)
set (GOOGLE_TEST_LIB_DIRS      ${GOOGLE_TEST_BASE_DIR})
set (GOOGLE_TEST_LIBRARIES     gtest)

# SceneR Framework
set (SCENER_FRAMEWORK_BASE_DIR     ${CMAKE_CURRENT_SOURCE_DIR}/SceneR)
set (SCENER_FRAMEWORK_INCLUDE_DIRS ${SCENER_FRAMEWORK_BASE_DIR}/Headers)
set (SCENER_FRAMEWORK_LIB_DIRS     ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE})
set (SCENER_FRAMEWORK_LIBRARIES    SceneR)

# Reconfigure final output directory
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE})
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE})
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE})

# Project subdirectories
add_subdirectory(SceneR)
add_subdirectory(RendererSample)
# add_subdirectory(SceneR.Framework.Tests)
