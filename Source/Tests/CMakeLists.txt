cmake_minimum_required (VERSION 3.2.2)
project (Tests)
enable_language(CXX)

# include directories
include_directories (${GSL_INCLUDE_DIRS}
                     ${GOOGLE_TEST_INCLUDE_DIRS}
                     ${SCENER_INCLUDE_DIRS}
                     ${CMAKE_CURRENT_SOURCE_DIR}/Headers)

# pthread
find_package (Threads REQUIRED)

# link directories
link_directories (${GOOGLE_TEST_LIB_DIRS} ${SCENER_FRAMEWORK_LIB_DIRS})

# header files
file (GLOB_RECURSE HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/Headers/*.hpp)

# source files
file (GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/Sources/*.cpp)

# add execlutable
add_executable (Tests ${HEADER_FILES} ${SOURCE_FILES})

# enable 64 bit build
set_target_properties (Tests PROPERTIES COMPILE_FLAGS -m64 LINK_FLAGS -m64 -nostdlib -nodefaultlibs)

# target links
target_link_libraries (Tests
                       c++abi
                       pthread
                       ${GOOGLE_TEST_LIBRARIES}
                       ${SCENER_LIBRARIES})
