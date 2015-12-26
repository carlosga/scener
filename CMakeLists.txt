cmake_minimum_required(VERSION 3.2.2)
enable_language(CXX)

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

# Reconfigure final output directory
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE})
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE})
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE})

# Project subdirectories
add_subdirectory(Source)
