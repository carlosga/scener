cmake_minimum_required(VERSION 3.2.2)
project(SceneR)
enable_language(CXX)

# set(CMAKE_VERBOSE_MAKEFILE on)

set (CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/installed" CACHE PATH "default install path" FORCE)

# enable c++11 & clang standard library
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++14 -stdlib=libc++ -g3 -O0 -Wall")

# Reconfigure final output directory
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE})
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE})
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE})

message (STATUS "Ouput Directory: " ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

# include directories
include_directories(Headers)

# link directories
link_directories(../../regal/lib/linux/
                 ../SceneR.Framework/build/${CMAKE_BUILD_TYPE})

# header files
set(HEADER_FILES
    Headers/Camera.hpp
    Headers/Marcus.hpp
    Headers/SampleModel.hpp
    Headers/SampleRenderer.hpp)

# source files
set(SOURCE_FILES
    Sources/Camera.cpp
    Sources/Marcus.cpp
    Sources/SampleModel.cpp
    Sources/SampleRenderer.cpp)

# add execlutable
add_executable(SceneR Sources/main.cpp ${HEADER_FILES} ${SOURCE_FILES})

# target include directories
target_include_directories(SceneR
                           PRIVATE ../../regal/include
                           PUBLIC ../SceneR.Framework/Headers)

# target libs
target_link_libraries(SceneR c++abi SceneR_Framework)

# enable 64 bit build
set_target_properties(SceneR PROPERTIES COMPILE_FLAGS -m64 LINK_FLAGS -m64)

# install executable file
install(TARGETS SceneR RUNTIME DESTINATION bin)

# install content files
install(DIRECTORY Content/ DESTINATION bin/Content)
