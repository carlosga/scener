# common include directories
include_directories (${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/samples)

# SceneR
set (SCENER_LIB_DIRS  ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE})
set (SCENER_LIBRARIES scener)

# Project subdirectories
add_subdirectory(scener)

# Tests subdirectories
add_subdirectory(tests)

# Samples subdirectories
add_subdirectory(samples)
