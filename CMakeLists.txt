cmake_minimum_required(VERSION 3.2.2)
project (scener::root)
enable_language (CXX)

# set (CMAKE_VERBOSE_MAKEFILE on)
set (CMAKE_EXPORT_COMPILE_COMMANDS on)

# external dependencies
#
# base directory
set (EXTERNALS_BASE_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/externals)

# json11
set (JSON11_INCLUDE_DIRS ${EXTERNALS_BASE_DIR}/json11)
set (JSON11_SOURCE_DIRS  ${EXTERNALS_BASE_DIR}/json11)

# microsoft/gsl
set (GSL_INCLUDE_DIRS    ${EXTERNALS_BASE_DIR}/gsl/include)

# nod/signals & slots (https://github.com/fr00b0/nod)
set (NOD_INCLUDE_DIRS    ${EXTERNALS_BASE_DIR}/nod/include)

# scener math
set (SCENER_MATH_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/../scener-math/include)

# Workaround using a local build of libc++ & libc++abi 3.8 under ubuntu 16.04
include_directories (/usr/local/include/c++/v1 /home/carlos/development/projects/cpp/libcxx/libcxxabi/include)
link_directories(/usr/local/lib)

# compiler and linker configurations
if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")

    set (CMAKE_CXX_FLAGS           "${CMAKE_CXX_FLAGS}           -m64 -stdlib=libc++ -std=c++14")
    set (CMAKE_EXE_LINKER_FLAGS    "${CMAKE_EXE_LINKER_FLAGS}    -m64 -stdlib=libc++ -lc++abi")
    set (CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -m64 -stdlib=libc++ -lc++abi")
    set (CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -m64 -stdlib=libc++ -lc++abi")

elseif ( "${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU" )

    set (CMAKE_CXX_FLAGS           "${CMAKE_CXX_FLAGS}           -m64 -std=c++14")
    set (CMAKE_EXE_LINKER_FLAGS    "${CMAKE_EXE_LINKER_FLAGS}    -m64")
    set (CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -m64")
    set (CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -m64")

else ()

    message ("-> unknown compiler ...")

endif ()

# reconfigure final output directory
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE})
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE})
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE})

# unit tests
enable_testing()

# project subdirectories
add_subdirectory (source)
