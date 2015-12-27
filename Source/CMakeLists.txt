# common include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# SceneR
set (SCENER_LIB_DIRS  ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE})
set (SCENER_LIBRARIES SceneR)

# Project subdirectories
add_subdirectory(SceneR)

# Tests subdirectories
add_subdirectory(Tests)

# Samples subdirectories
# add_subdirectory(Samples)
