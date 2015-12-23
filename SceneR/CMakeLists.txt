project (SceneR)

# include directories
include_directories (${JSON11_INCLUDE_DIRS}
                     ${GSL_INCLUDE_DIRS}
                     ${OPENGL_INCLUDE_DIRS}
                     ${GLFW_INCLUDE_DIRS}
                     ${SCENER_FRAMEWORK_INCLUDE_DIRS}
                     Headers)

# PkgConfig
find_package (PkgConfig REQUIRED)

# pthread
find_package (Threads REQUIRED)

# OpenGL
find_package (OpenGL REQUIRED)

# glfw
pkg_search_module (GLFW REQUIRED glfw3)

# link directories
link_directories (${SCENER_FRAMEWORK_LIB_DIRS})

# header files
set (HEADER_FILES
     Headers/Camera.hpp
     Headers/EarthShaker.hpp
     Headers/SampleRenderer.hpp)

# source files
set (SOURCE_FILES
     Sources/Camera.cpp
     Sources/EarthShaker.cpp
     Sources/SampleRenderer.cpp
     Sources/main.cpp)

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
                       ${OPENGL_LIBRARIES}
                       ${GLFW_LIBRARIES}
                       SceneR_Framework)

file(COPY Content DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
