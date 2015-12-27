cmake_minimum_required (VERSION 3.2.2)
project (SceneR)
enable_language(CXX)

# pthread
find_package (Threads REQUIRED)

# OpenGL
find_package (OpenGL REQUIRED)

# X11
find_package (X11 REQUIRED)

# header files
file (GLOB_RECURSE HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)

# source files
file (GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# library output
add_library (SceneR SHARED ${HEADER_FILES} ${SOURCE_FILES} ${JSON11_SOURCE_DIRS}/json11.cpp)

# include directories
target_include_directories (SceneR
                            PRIVATE ${X11_INCLUDE_DIR}
                            PRIVATE ${JSON11_INCLUDE_DIRS}
                            PRIVATE ${GSL_INCLUDE_DIRS})

# target links
target_link_libraries (SceneR c++abi pthread ${X11_LIBRARIES})
