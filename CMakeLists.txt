cmake_minimum_required(VERSION 3.2.2)
project (scener)
enable_language (CXX)

# set (CMAKE_VERBOSE_MAKEFILE on)
set (CMAKE_EXPORT_COMPILE_COMMANDS on)

# cmake modules
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# external dependencies
# base directory
set (EXTERNALS_BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/externals)

# microsoft/gsl
set (GSL_INCLUDE_DIRS ${EXTERNALS_BASE_DIR}/gsl/include)

# json for modern C++
set (JSON_INCLUDE_DIRS ${EXTERNALS_BASE_DIR}/json/single_include)

# nod/signals & slots (https://github.com/fr00b0/nod)
set (NOD_INCLUDE_DIRS ${EXTERNALS_BASE_DIR}/nod/include)

# scener math
set (SCENER_MATH_INCLUDE_DIRS ${EXTERNALS_BASE_DIR}/scener-math/include)

# AMD VULKAN MEMORY ALLOCATOR
set (AMD_VULKAN_MEMORY_ALLOCATOR_INCLUDE_DIRS ${EXTERNALS_BASE_DIR}/vulkan-memory-allocator/include)

# reconfigure final output directory
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE})
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE})
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE})

# compiler flags
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64 -std=c++17")

# common ompile options
if (${CMAKE_BUILD_TYPE} MATCHES "Debug")

    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-unused-parameter -Wno-exceptions")

endif ()

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")

  # compiler flags
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")

  # linker flags
  set (CMAKE_EXE_LINKER_FLAGS    "${CMAKE_EXE_LINKER_FLAGS}    -lc++ -lc++abi")
  set (CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -lc++ -lc++abi")
  set (CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -lc++ -lc++abi")

elseif ( "${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU" )

    if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
        set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-terminate -Wnull-dereference -Wduplicated-cond -Wduplicated-branches -Wlogical-op")
    endif()

else ()
    message ("-> unknown compiler ...")
endif ()

# SceneR
set (SCENER_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/source)
set (SCENER_LIB_DIRS     ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE})
set (SCENER_LIBRARIES    scener)

# global definitions
set (VK_USE_PLATFORM_WAYLAND_KHR "0")
set (VK_USE_PLATFORM_XCB_KHR "1")
set (VK_ENABLE_DEBUG_SUPPORT "0")

# project subdirectories
add_subdirectory (source)

# unit tests
# enable_testing()
# add_subdirectory(tests)
