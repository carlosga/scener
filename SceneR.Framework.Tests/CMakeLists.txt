project (SceneR_Framework_Tests)

# include directories
include_directories (${JSON11_INCLUDE_DIRS}
                     ${GSL_INCLUDE_DIRS}
                     ${OPENGL_INCLUDE_DIRS}
                     ${GLFW_INCLUDE_DIRS}
                     ${GOOGLE_TEST_INCLUDE_DIRS}
                     ${SCENER_FRAMEWORK_INCLUDE_DIRS}
                     Headers)

# PkgConfig
find_package (PkgConfig REQUIRED)

# pthread
find_package (Threads REQUIRED)

# OpenGL
find_package (OpenGL REQUIRED)

# glfw
pkg_search_module (GLFW REQUIRED glfw3)

# link directories
link_directories (${GOOGLE_TEST_LIB_DIRS} ${SCENER_FRAMEWORK_LIB_DIRS})

# header files
set (HEADER_FILES
     Headers/EqualityHelper.hpp
     Headers/BinaryReaderTest.hpp
     Headers/EncodingUTF8Test.hpp
     Headers/FileStreamTest.hpp
     Headers/MathTest.hpp
     Headers/MatrixTest.hpp
     Headers/MemoryStreamTest.hpp
     Headers/PlaneTest.hpp
     Headers/QuaternionTest.hpp
     Headers/TimeSpanTest.hpp
     Headers/UTF8EncodingTest.hpp
     Headers/Vector2Test.hpp
     Headers/Vector3Test.hpp
     Headers/Vector4Test.hpp)

# source files
set (SOURCE_FILES
     Sources/EqualityHelper.cpp
     Sources/BinaryReaderTest.cpp
     Sources/EncodingUTF8Test.cpp
     Sources/FileStreamTest.cpp
     Sources/MathTest.cpp
     Sources/MatrixTest.cpp
     Sources/MemoryStreamTest.cpp
     Sources/PlaneTest.cpp
     Sources/QuaternionTest.cpp
     Sources/TimeSpanTest.cpp
     Sources/UTF8EncodingTest.cpp
     Sources/Vector2Test.cpp
     Sources/Vector3Test.cpp
     Sources/Vector4Test.cpp
     Sources/TestRunner.cpp)

# add execlutable
add_executable (SceneR_Framework_Tests ${HEADER_FILES} ${SOURCE_FILES})

# enable 64 bit build
set_target_properties (SceneR_Framework_Tests PROPERTIES COMPILE_FLAGS -m64 LINK_FLAGS -m64 -nostdlib -nodefaultlibs)

# target links
target_link_libraries (SceneR_Framework_Tests
                       c++abi
                       pthread
                       ${GOOGLE_TEST_LIBRARIES}
                       ${OPENGL_LIBRARIES}
                       ${GLFW_LIBRARIES}
                       SceneR_Framework)
