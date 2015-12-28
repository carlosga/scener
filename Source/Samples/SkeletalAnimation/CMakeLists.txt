cmake_minimum_required (VERSION 3.2.2)
project (SceneR::Samples::SkeletalAnimation)
enable_language(CXX)

# include directories
include_directories (${JSON11_INCLUDE_DIRS}
                     ${GSL_INCLUDE_DIRS}
                     ${SCENER_FRAMEWORK_INCLUDE_DIRS})

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
                   Content/earthshaker/earthshaker.gltf
                   Content/earthshaker/earthshaker0CB.glsl
                   Content/earthshaker/earthshaker0FS.glsl
                   Content/earthshaker/earthshaker0VS.glsl
                   Content/earthshaker/structures.glsl
                   Content/earthshaker/common.glsl
                   Content/earthshaker/skinning.glsl)

# source files
file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# add execlutable
add_executable (SkeletalAnimation ${SOURCE_FILES})

# enable 64 bit build
set_target_properties (SkeletalAnimation PROPERTIES COMPILE_FLAGS -m64 LINK_FLAGS -m64 -nostdlib -nodefaultlibs)

# target links
target_link_libraries (SkeletalAnimation
                       c++abi
                       pthread
                       ${SCENER_LIBRARIES})

# copy content files
add_custom_command (TARGET SkeletalAnimation PRE_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_directory
                    ${CMAKE_CURRENT_SOURCE_DIR}/Content ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Content)
