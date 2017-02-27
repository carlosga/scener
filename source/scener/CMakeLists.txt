cmake_minimum_required (VERSION 3.2.2)
project (scener)
enable_language (CXX)

# compile options
# if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
#   add_compile_options(-Wall -Wextra -Wno-unused-parameter)

#   add_compile_options(-Weverything                -Wno-reserved-id-macro
#                       -Wno-c++98-compat           -Wno-c++98-compat-pedantic
#                       -Wno-gnu-anonymous-struct   -Wno-nested-anon-types
#                       -Wno-weak-vtables           -Wno-padded
#                       -Wno-float-equal            
#                       -Wno-global-constructors    -Wno-exit-time-destructors)
# endif ()

# pthread
find_package (Threads REQUIRED)

# X11
find_package (X11 REQUIRED)

# OpenGL
find_package (OpenGL REQUIRED)

# source files
file (GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# library output
add_library (scener SHARED ${HEADER_FILES} ${SOURCE_FILES})

# include directories
target_include_directories (scener
                            PRIVATE ${X11_INCLUDE_DIR}
                            PRIVATE ${JSON_INCLUDE_DIRS}
                            PRIVATE ${GSL_INCLUDE_DIRS}
                            PRIVATE ${NOD_INCLUDE_DIRS}
                            PRIVATE ${SCENER_MATH_INCLUDE_DIRS}
                            PRIVATE ${SCENER_INCLUDE_DIRS})

# target links
target_link_libraries (scener pthread ${X11_LIBRARIES} ${OPENGL_LIBRARIES})
