cmake_minimum_required (VERSION 3.2.2)
project (scener::framework)
enable_language (CXX)

# source files
file (GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file (GLOB_RECURSE HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)

# library output
add_library (scener SHARED ${SOURCE_FILES} ${HEADER_FILES})

# include directories
target_include_directories (scener
                            PUBLIC ${VULKAN_INCLUDE_DIR}
                            PUBLIC ${AMD_VULKAN_MEMORY_ALLOCATOR_INCLUDE_DIRS}
                            PUBLIC ${JSON_INCLUDE_DIRS}
                            PUBLIC ${GSL_INCLUDE_DIRS}
                            PUBLIC ${NOD_INCLUDE_DIRS}
                            PUBLIC ${SCENER_MATH_INCLUDE_DIRS}
                            PUBLIC ${SCENER_INCLUDE_DIRS})

# target links
target_link_libraries (scener ${VULKAN_LIBRARIES})
