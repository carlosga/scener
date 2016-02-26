cmake_minimum_required (VERSION 3.2.2)
project (SceneR::Samples::skeletal-animation)
enable_language(CXX)

# include directories
#include_directories (${JSON11_INCLUDE_DIRS}
#                     ${GSL_INCLUDE_DIRS}
#                     ${NOD_INCLUDE_DIRS}
#                     ${SCENER_FRAMEWORK_INCLUDE_DIRS})

# pthread
find_package (Threads REQUIRED)

# OpenGL
find_package (OpenGL REQUIRED)

# X11
find_package (X11 REQUIRED)

# link directories
link_directories (${SCENER_FRAMEWORK_LIB_DIRS})

# content files
add_custom_target (CONTENT_FILES SOURCES
                   content/earthshaker/earthshaker.gltf
                   content/earthshaker/earthshaker0CB.glsl
                   content/earthshaker/earthshaker0FS.glsl
                   content/earthshaker/earthshaker0VS.glsl
                   content/earthshaker/structures.glsl
                   content/earthshaker/common.glsl
                   content/earthshaker/skinning.glsl)

# source files
file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# add execlutable
add_executable (skeletal-animation ${SOURCE_FILES})

# enable 64 bit build
set_target_properties (skeletal-animation PROPERTIES COMPILE_FLAGS -m64 LINK_FLAGS -m64 -nostdlib -nodefaultlibs)

# include directories
target_include_directories (skeletal-animation
                            PRIVATE ${JSON11_INCLUDE_DIRS}
                            PRIVATE ${GSL_INCLUDE_DIRS}
                            PRIVATE ${NOD_INCLUDE_DIRS}
                            PRIVATE ${SCENER_MATH_INCLUDE_DIRS}
                            PRIVATE ${SCENER_FRAMEWORK_INCLUDE_DIRS})

# target links
target_link_libraries (skeletal-animation
                       c++abi
                       pthread
                       ${SCENER_LIBRARIES})

# copy content files
add_custom_command (TARGET skeletal-animation PRE_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_directory
                    ${CMAKE_CURRENT_SOURCE_DIR}/content ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/content)
