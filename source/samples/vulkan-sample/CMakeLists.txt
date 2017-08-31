cmake_minimum_required (VERSION 3.2.2)
project (scener::samples::vulkan::sample)
enable_language (CXX)

# pthread
find_package (Threads REQUIRED)

# link directories
link_directories (${SCENER_FRAMEWORK_LIB_DIRS})

# source files
file (GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# add execlutable
add_executable (vulkan-sample ${SOURCE_FILES})

# include directories
target_include_directories (vulkan-sample
                            PRIVATE ${GSL_INCLUDE_DIRS}
                            PRIVATE ${NOD_INCLUDE_DIRS}
                            PRIVATE ${SCENER_MATH_INCLUDE_DIRS}
                            PRIVATE ${SCENER_INCLUDE_DIRS}
                            PRIVATE ${SCENER_SAMPLES_INCLUDE_DIR})

# target links
target_link_libraries (vulkan-sample pthread ${SCENER_LIBRARIES})
