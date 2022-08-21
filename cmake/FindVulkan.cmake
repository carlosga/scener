# https://gist.github.com/Grimeh/3d9762adfdc555715c1b
#
# To install this, place in [Project root]/cmake/Modules/ or <CMAKE_ROOT>/share/cmake-x.y/Modules/
# - Try to find Vulkan SDK
# If successful, will define:
#	VULKAN_FOUND
#	VULKAN_INCLUDE_DIRS
#	VULKAN_LIBRARIES
#	VULKAN_DEFINITIONS

find_package (PkgConfig)

set (VULKAN_DEFINITIONS) # nothing

find_path (VULKAN_INCLUDE_DIR NAMES vulkan/vulkan.h HINTS "$ENV{VK_INCLUDE_PATH}/include")
find_library (VULKAN_LIBRARY NAMES vulkan HINTS "$ENV{VK_LIBRARY_PATH}")

set (VULKAN_LIBRARIES    ${VULKAN_LIBRARY})
set (VULKAN_INCLUDE_DIRS ${VULKAN_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Vulkan DEFAULT_MSG VULKAN_LIBRARY VULKAN_INCLUDE_DIR)

mark_as_advanced(VULKAN_INCLUDE_DIR VULKAN_LIBRARY)
