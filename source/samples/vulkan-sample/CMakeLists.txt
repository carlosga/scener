cmake_minimum_required (VERSION 3.2.2)
project (scener::samples::vulkan::sample)
enable_language (CXX)

# pthread
find_package (Threads REQUIRED)

# OpenGL
find_package (Vulkan REQUIRED)

# X11
find_package (X11 REQUIRED)

# XCB
find_package (XCB REQUIRED)

# link directories
link_directories (${SCENER_FRAMEWORK_LIB_DIRS})

# source files
file (GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# add execlutable
add_executable (vulkan-sample ${SOURCE_FILES})

# include directories
target_include_directories (vulkan-sample
                            PRIVATE ${VULKAN_INCLUDE_DIR}
                            PRIVATE ${VULKAN_HPP_INCLUDE_DIR}
                            PRIVATE ${GSL_INCLUDE_DIRS}
                            PRIVATE ${NOD_INCLUDE_DIRS}
                            PRIVATE ${SCENER_MATH_INCLUDE_DIRS}
                            PRIVATE ${SCENER_INCLUDE_DIRS}
                            PRIVATE ${SCENER_SAMPLES_INCLUDE_DIR})

# target links
target_link_libraries (vulkan-sample pthread ${SCENER_LIBRARIES})

# target definitions
target_compile_definitions(vulkan-sample PRIVATE -DVK_USE_PLATFORM_XCB_KHR)
