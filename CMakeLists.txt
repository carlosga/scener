cmake_minimum_required(VERSION 3.2.2)
project (scener::root)
enable_language (CXX)

# set (CMAKE_VERBOSE_MAKEFILE on)
set (CMAKE_EXPORT_COMPILE_COMMANDS on)

# external dependencies
#
# base directory
set (EXTERNALS_BASE_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/externals)

# json for modern C++
set (JSON_INCLUDE_DIRS ${EXTERNALS_BASE_DIR}/json/src)

# microsoft/gsl
set (GSL_INCLUDE_DIRS    ${EXTERNALS_BASE_DIR}/gsl/include)

# nod/signals & slots (https://github.com/fr00b0/nod)
set (NOD_INCLUDE_DIRS    ${EXTERNALS_BASE_DIR}/nod/include)

# scener math
set (SCENER_MATH_INCLUDE_DIRS ${EXTERNALS_BASE_DIR}/scener-math/source)

# Workaround using a local build of libc++ & libc++abi 3.8 under ubuntu 16.04
# Workaround using a local build of libc++ & libc++abi 3.9 under ubuntu 16.04
if (CMAKE_LIBCXX_INCLUDE_PATH)
    include_directories (${CMAKE_LIBCXX_INCLUDE_PATH} ${CMAKE_LIBCXXABI_INCLUDE_PATH})
endif ()
if (CMAKE_LIBCXXABI_LIB_PATH)
    link_directories(${CMAKE_LIBCXXABI_LIB_PATH})
endif ()

# compiler and linker configurations
if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")

    set (CMAKE_CXX_FLAGS           "${CMAKE_CXX_FLAGS}           -m64 -stdlib=libc++ -std=c++1z")
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

# project subdirectories
add_subdirectory (source)

# unit tests
enable_testing()
