cmake_minimum_required (VERSION 3.2.2)
project (scener::tests)
enable_language (CXX)

# google test
# http://crascit.com/2015/07/25/cmake-gtest/

if (CMAKE_VERSION VERSION_LESS 3.2)
    set(UPDATE_DISCONNECTED_IF_AVAILABLE "")
else()
    set(UPDATE_DISCONNECTED_IF_AVAILABLE "UPDATE_DISCONNECTED 1")
endif()

include(DownloadProject.cmake)
download_project(PROJ           googletest
                 GIT_REPOSITORY https://github.com/google/googletest.git
                 GIT_TAG        master
                 ${UPDATE_DISCONNECTED_IF_AVAILABLE})

# Add googletest directly to our build. This adds
# the following targets: gtest, gtest_main, gmock
# and gmock_main
add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR} EXCLUDE_FROM_ALL)

# pthread
find_package (Threads REQUIRED)

# link directories
link_directories (${CMAKE_BINARY_DIR}/googletest-build ${SCENER_LIB_DIRS})

# header files
file (GLOB_RECURSE HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)

# source files
file (GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# add execlutable
add_executable (test_runner ${HEADER_FILES} ${SOURCE_FILES})

# target include directories
target_include_directories(test_runner PRIVATE ${GSL_INCLUDE_DIRS} PRIVATE ${SCENER_INCLUDE_DIRS})

# target links
target_link_libraries (test_runner pthread gtest ${SCENER_LIBRARIES})

# unit tests
add_test(NAME scener_test_runner COMMAND test_runner)
