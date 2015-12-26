cmake_minimum_required (VERSION 3.2.2)
project (SceneR)
enable_language(CXX)

# include directories
include_directories (${JSON11_INCLUDE_DIRS}
                     ${GSL_INCLUDE_DIRS}
                     ${SCENER_FRAMEWORK_INCLUDE_DIRS}
                     ${CMAKE_CURRENT_SOURCE_DIR}/Headers)

# pthread
find_package (Threads REQUIRED)

# OpenGL
find_package (OpenGL REQUIRED)

# X11
find_package (X11 REQUIRED)

# link directories
link_directories (${SCENER_FRAMEWORK_LIB_DIRS})

# header files
file(GLOB_RECURSE HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/Headers/*.hpp)

# source files
file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/Sources/*.cpp)

# Content files
add_custom_target (CONTENT_FILES SOURCES
                   Content/earthshaker/earthshaker.gltf
                   Content/earthshaker/earthshaker0CB.glsl
                   Content/earthshaker/earthshaker0FS.glsl
                   Content/earthshaker/earthshaker0VS.glsl
                   Content/earthshaker/structures.glsl
                   Content/earthshaker/common.glsl
                   Content/earthshaker/skinning.glsl)

# add execlutable
add_executable (SceneR ${HEADER_FILES} ${SOURCE_FILES})

# enable 64 bit build
set_target_properties (SceneR PROPERTIES COMPILE_FLAGS -m64 LINK_FLAGS -m64 -nostdlib -nodefaultlibs)

# target links
target_link_libraries (SceneR
                       c++abi
                       pthread
                       ${SCENER_FRAMEWORK_LIBRARIES})

file (COPY Content DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
