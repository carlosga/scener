cmake_minimum_required(VERSION 2.8.4)
project(SceneR_Framework_Tests)
enable_language(CXX)

set(CMAKE_C_COMPILER clang-3.5)
set(CMAKE_CXX_COMPILER clang++-3.5)

# enable c++11 & clang standard library
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -stdlib=libc++ -g3 -Wall -O0")

# include directories
include_directories(Headers
                    ../SceneR.Framework/Headers
                    ../../regal/include
                    ../../gtest-1.7.0/include)

# pthread
find_package(Threads REQUIRED)

# glfw
find_package(glfw REQUIRED)

# Regal
# Google Tests
link_directories(../../regal/lib/linux/
                 ../../gtest-1.7.0)

# header files
set(HEADER_FILES
    Headers/EqualityHelper.hpp
    Headers/BinaryReaderTest.hpp
    Headers/EncodingUTF8Test.hpp
    Headers/FileStreamTest.hpp
    Headers/MathHelperTest.hpp
    Headers/MatrixTest.hpp
    Headers/PlaneTest.hpp
    Headers/QuaternionTest.hpp
    Headers/TimeSpanTest.hpp
    Headers/Vector2Test.hpp
    Headers/Vector3Test.hpp
    Headers/Vector4Test.hpp)

# source files
set(SOURCE_FILES
    Sources/EqualityHelper.cpp
    Sources/BinaryReaderTest.cpp
    Sources/EncodingUTF8Test.cpp
    Sources/FileStreamTest.cpp
    Sources/MathHelperTest.cpp
    Sources/MatrixTest.cpp
    Sources/PlaneTest.cpp
    Sources/QuaternionTest.cpp
    Sources/TimeSpanTest.cpp
    Sources/Vector2Test.cpp
    Sources/Vector3Test.cpp
    Sources/Vector4Test.cpp)

# add execlutable
add_executable(SceneR_Framework_Tests Sources/TestRunner.cpp ${HEADER_FILES} ${SOURCE_FILES})

# target libs
target_link_libraries(SceneR_Framework_Tests gtest SceneR_Framework)

# enable 64 bit build
set_target_properties(SceneR_Framework_Tests PROPERTIES COMPILE_FLAGS -m64 LINK_FLAGS -m64)

# Installing
install(TARGETS SceneR_Framework_Tests DESTINATION bin)
