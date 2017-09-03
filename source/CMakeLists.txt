# common ompile options
if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
  add_compile_options(-Wall -Wextra -Wno-unused-parameter)
endif ()

# pthread
find_package (Threads REQUIRED)

# common link libraries
link_libraries(${CMAKE_THREAD_LIBS_INIT})

# X11/XCB
if (${VK_USE_PLATFORM_XCB_KHR} MATCHES "1")
  # definitions
  add_definitions(-DVK_USE_PLATFORM_XCB_KHR)

  # X11
  find_package (X11 REQUIRED)

  # XCB
  find_package (XCB REQUIRED)

  #include directories
  include_directories(
    PUBLIC ${X11_INCLUDE_DIR}
    PUBLIC ${XCB_INCLUDE_DIRS}
  )

  # libraries
  link_libraries(${X11_LIBRARIES} ${XCB_LIBRARIES})  
endif()

# Wayland
if (${VK_USE_PLATFORM_WAYLAND_KHR} MATCHES "1") 
  # definitions
  add_definitions(-DVK_USE_PLATFORM_WAYLAND_KHR) 

  # X11
  find_package (X11 REQUIRED)

  # Wayland
  find_package (Wayland REQUIRED)

  #include directories
  include_directories(PUBLIC ${WAYLAND_CLIENT_INCLUDE_DIR})
  
  # libraries
  link_libraries(${X11_LIBRARIES} ${WAYLAND_CLIENT_LIBRARIES})
endif()

# Project subdirectories
add_subdirectory(scener)

# Samples subdirectories
add_subdirectory(samples)
