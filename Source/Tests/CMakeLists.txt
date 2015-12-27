cmake_minimum_required (VERSION 3.2.2)
project (Tests)
enable_language(CXX)

# pthread
find_package (Threads REQUIRED)

# link directories
link_directories (${GOOGLE_TEST_LIB_DIRS} ${SCENER_LIB_DIRS})

# header files
file (GLOB_RECURSE HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)

# source files
file (GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# add execlutable
add_executable (Tests ${SOURCE_FILES})

# target include directories
target_include_directories(Tests
                           PRIVATE ${GSL_INCLUDE_DIRS}
                           PRIVATE ${GOOGLE_TEST_INCLUDE_DIRS}
                           PRIVATE ${SCENER_INCLUDE_DIRS})

# target links
target_link_libraries (Tests
                       c++abi
                       pthread
                       ${GOOGLE_TEST_LIBRARIES}
                       ${SCENER_LIBRARIES})
