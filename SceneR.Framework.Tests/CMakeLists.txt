cmake_minimum_required(VERSION 3.2.2)
project(SceneR_Framework_Tests)
enable_language(CXX)

# enable c++11 & clang standard library
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++14 -stdlib=libc++ -g3 -O0 -Wall")

# Reconfigure final output directory
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE})
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE})
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE})

message (STATUS "Ouput Directory: " ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

# include directories
include_directories(Headers
                    ../../regal/include
                    ../SceneR.Framework/Headers
                    ../../gtest-1.7.0/include)

# PkgConfig
find_package(PkgConfig REQUIRED)

# pthread
find_package(Threads REQUIRED)

# Regal
# SceneR Framework
# Google Tests
link_directories(../../regal/lib/linux/
                 ../SceneR.Framework/build/${CMAKE_BUILD_TYPE}
                 ../../gtest-1.7.0)

# header files
set(HEADER_FILES
    Headers/EqualityHelper.hpp
    Headers/BinaryReaderTest.hpp
    Headers/EncodingUTF8Test.hpp
    Headers/FileStreamTest.hpp
    Headers/MathTest.hpp
    Headers/MatrixTest.hpp
    Headers/PlaneTest.hpp
    Headers/QuaternionTest.hpp
    Headers/TimeSpanTest.hpp
    Headers/UTF8EncodingTest.hpp
    Headers/Vector2Test.hpp
    Headers/Vector3Test.hpp
    Headers/Vector4Test.hpp)

# source files
set(SOURCE_FILES
    Sources/EqualityHelper.cpp
    Sources/BinaryReaderTest.cpp
    Sources/EncodingUTF8Test.cpp
    Sources/FileStreamTest.cpp
    Sources/MathTest.cpp
    Sources/MatrixTest.cpp
    Sources/PlaneTest.cpp
    Sources/QuaternionTest.cpp
    Sources/TimeSpanTest.cpp
    Sources/UTF8EncodingTest.cpp
    Sources/Vector2Test.cpp
    Sources/Vector3Test.cpp
    Sources/Vector4Test.cpp)

# add execlutable
add_executable(SceneR_Framework_Tests Sources/TestRunner.cpp ${HEADER_FILES} ${SOURCE_FILES})

# target libs
target_link_libraries(SceneR_Framework_Tests c++abi gtest SceneR_Framework)

# enable 64 bit build
set_target_properties(SceneR_Framework_Tests PROPERTIES COMPILE_FLAGS -m64 LINK_FLAGS -m64)

# Installing
install(TARGETS SceneR_Framework_Tests DESTINATION bin)
