cmake_minimum_required(VERSION 2.8.4)
project(SceneR)
enable_language(CXX)

set(CMAKE_C_COMPILER clang-3.5)
set(CMAKE_CXX_COMPILER clang++-3.5)

# enable c++11 & clang standard library
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -stdlib=libc++ -g3 -Wall -O0")

# include directory
include_directories(Headers
                    ../SceneR.Framework/Headers
                    ../../regal/include)

# Regal
link_directories(../../regal/lib/linux/)

# header files
set(HEADER_FILES
    Headers/AstroBoy.hpp
    Headers/BumbleBee.hpp
    Headers/Felicia.hpp
    Headers/Marcus.hpp
    Headers/SampleRenderer.hpp
    Headers/WarForrest.hpp)

# source files
set(SOURCE_FILES
    Sources/AstroBoy.cpp
    Sources/BumbleBee.cpp
    Sources/Felicia.cpp
    Sources/Marcus.cpp
    Sources/SampleRenderer.cpp
    Sources/WarForrest.cpp)

# add execlutable
add_executable(SceneR Sources/main.cpp ${HEADER_FILES} ${SOURCE_FILES})

# target libs
target_link_libraries(SceneR SceneR_Framework) ## Regal

# enable 64 bit build
set_target_properties(SceneR PROPERTIES COMPILE_FLAGS -m64 LINK_FLAGS -m64)

# Installing
## install(TARGETS SceneR.Framework DESTINATION bin)
install(TARGETS SceneR DESTINATION bin)
