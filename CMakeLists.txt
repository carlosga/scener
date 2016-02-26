cmake_minimum_required(VERSION 3.2.2)
project (SceneR::Root)
enable_language(CXX)

# set (CMAKE_VERBOSE_MAKEFILE on)
set (CMAKE_EXPORT_COMPILE_COMMANDS on)

# external dependencies
#
# base directory
set (EXTERNALS_BASE_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/externals)

# json11
set (JSON11_INCLUDE_DIRS ${EXTERNALS_BASE_DIR}/json11)
set (JSON11_SOURCE_DIRS  ${EXTERNALS_BASE_DIR}/json11)

# Microsoft/GSL
set (GSL_INCLUDE_DIRS    ${EXTERNALS_BASE_DIR}/gsl/include)

# Nod/Signals & Slots (https://github.com/fr00b0/nod)
set (NOD_INCLUDE_DIRS    ${EXTERNALS_BASE_DIR}/nod/include)

# scener math
set (SCENER_MATH_INCLUDE_DIRS /home/carlos/development/projects/cpp/graphics/scener-math/include)

# compiler and linker configurations
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -stdlib=libc++ -m64")
#set (CMAKE_EXE_LINKER_FLAGS    "${CMAKE_EXE_LINKER_FLAGS}    -m64")
#set (CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -m64")
#set (CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -m64")

#if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
#    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3 -O0 -Wall -Wextra -Wno-unused-parameter")
#endif ()

# reconfigure final output directory
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE})
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE})
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE})

# unit tests
enable_testing()

# project subdirectories
add_subdirectory (source)
