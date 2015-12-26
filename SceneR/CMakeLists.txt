cmake_minimum_required (VERSION 3.2.2)
project (SceneR)
enable_language(CXX)

# include directories
include_directories (${JSON11_INCLUDE_DIRS}
                     ${GSL_INCLUDE_DIRS}
                     ${X11_INCLUDE_DIR}
                     ${CMAKE_CURRENT_SOURCE_DIR}/Headers)

# pthread
find_package (Threads REQUIRED)

# OpenGL
find_package (OpenGL REQUIRED)

# X11
find_package (X11 REQUIRED)

# header files
file (GLOB_RECURSE HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/Headers/*.hpp)

# source files
file (GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/Sources/*.cpp)

# library output
add_library (SceneR SHARED ${HEADER_FILES} ${SOURCE_FILES})

# enable 64 bit build
set_target_properties (SceneR PROPERTIES COMPILE_FLAGS -m64 LINK_FLAGS -m64 -nostdlib -nodefaultlibs)

# target sources
target_sources (SceneR PRIVATE ${JSON11_SOURCE_DIRS}/json11.cpp)

# target links
target_link_libraries (SceneR
                       c++abi
                       pthread
                       ${X11_LIBRARIES})

#                       Xi
#                       Xrandr
#                       Xxf86vm
#                       Xinerama
#                       Xcursor
#                       rt
#                       m
