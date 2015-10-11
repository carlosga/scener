cmake_minimum_required (VERSION 3.2.2)
project (SceneR)
enable_language (CXX)

# enable c++11 & clang standard library
set (CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++14 -stdlib=libc++ -g3 -O0 -Wall")

# Reconfigure final output directory
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE})
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE})
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE})

# External dependencies
#
# Base directory
set (EXTERNALS_BASE_DIR  ../externals)
# Microsoft/GSL
set (GSL_INCLUDE_DIRS    ${EXTERNALS_BASE_DIR}/gsl/include)

# Dependencies
#
# SceneR Framework
set (SCENER_FRAMEWORK_BASE_DIR    ../SceneR.Framework)
set (SCENER_FRAMEWORK_INCLUDE_DIRS ${SCENER_FRAMEWORK_BASE_DIR}/Headers)
set (SCENER_FRAMEWORK_LIB_DIRS     ${SCENER_FRAMEWORK_BASE_DIR}/build/${CMAKE_BUILD_TYPE})

# include directories
include_directories (Headers ${GSL_INCLUDE_DIRS} ${SCENER_FRAMEWORK_INCLUDE_DIRS})

# link directories
link_directories (${SCENER_FRAMEWORK_LIB_DIRS})

# header files
set (HEADER_FILES
     ${GSL_INCLUDE_DIRS}/gsl.h
     Headers/Camera.hpp
     Headers/EarthShaker.hpp
     Headers/SampleRenderer.hpp)

# source files
set (SOURCE_FILES
     Sources/Camera.cpp
     Sources/EarthShaker.cpp
     Sources/SampleRenderer.cpp)

add_custom_target (CONTENT_FILES SOURCES
                   Content/earthshaker/earthshaker.gltf
                   Content/earthshaker/earthshaker0CB.glsl
                   Content/earthshaker/earthshaker0FS.glsl
                   Content/earthshaker/earthshaker0VS.glsl
                   Content/earthshaker/structures.glsl
                   Content/earthshaker/common.glsl
                   Content/earthshaker/skinning.glsl)

# add execlutable
add_executable (SceneR Sources/main.cpp ${HEADER_FILES} ${SOURCE_FILES})

# target include directories
target_include_directories (SceneR
                            PUBLIC ${GSL_INCLUDE_DIRS}
                            PUBLIC ${SCENER_FRAMEWORK_INCLUDE_DIRS})

# target libs
target_link_libraries (SceneR c++abi SceneR_Framework)

# enable 64 bit build
set_target_properties (SceneR PROPERTIES COMPILE_FLAGS -m64 LINK_FLAGS -m64 -nostdlib -nodefaultlibs)