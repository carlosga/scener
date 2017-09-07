cmake_minimum_required (VERSION 3.2.2)
project (scener)
enable_language (CXX)

# Vulkan
find_package (Vulkan REQUIRED)

# source files
file (GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file (GLOB_RECURSE HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)

# library output
add_library (scener SHARED ${SOURCE_FILES} ${HEADER_FILES})

# include directories
target_include_directories (scener
                            PUBLIC  ${VULKAN_INCLUDE_DIR}
                            PRIVATE ${AMD_VULKAN_MEMORY_ALLOCATOR_INCLUDE_DIRS}
                            PRIVATE ${JSON_INCLUDE_DIRS}
                            PRIVATE ${GSL_INCLUDE_DIRS}
                            PRIVATE ${NOD_INCLUDE_DIRS}
                            PRIVATE ${SCENER_MATH_INCLUDE_DIRS}
                            PRIVATE ${SCENER_INCLUDE_DIRS})

# target links
target_link_libraries (scener ${VULKAN_LIBRARIES})
