cmake_minimum_required (VERSION 3.2.2)
project (scener::samples::skeletal-animation)
enable_language (CXX)

# link directories
link_directories (${SCENER_FRAMEWORK_LIB_DIRS})

# content files ( models, shaders, textures, etc. )
file (GLOB_RECURSE CONTENT_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/content/**)

# content files
add_custom_target (CONTENT_FILES SOURCES ${CONTENT_SOURCE_FILES})

# source files
file (GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# add execlutable
add_executable (skeletal-animation ${SOURCE_FILES})

# include directories
target_include_directories (skeletal-animation
                            PRIVATE ${GSL_INCLUDE_DIRS}
                            PRIVATE ${NOD_INCLUDE_DIRS}
                            PRIVATE ${SCENER_MATH_INCLUDE_DIRS}
                            PRIVATE ${SCENER_INCLUDE_DIRS}
                            PRIVATE ${SCENER_SAMPLES_INCLUDE_DIR})

# target links
target_link_libraries (skeletal-animation pthread ${SCENER_LIBRARIES})

# compile shaders
set (GLSL_VALIDATOR "$ENV{GLSL_LANG_PATH}/glslangValidator")

# GLSL shader files
file (GLOB_RECURSE GLSL_SOURCE_FILES
      ${CMAKE_CURRENT_SOURCE_DIR}/content/**/*.vert
      ${CMAKE_CURRENT_SOURCE_DIR}/content/**/*.frag
      ${CMAKE_CURRENT_SOURCE_DIR}/content/**/*.tesc
      ${CMAKE_CURRENT_SOURCE_DIR}/content/**/*.tese
      ${CMAKE_CURRENT_SOURCE_DIR}/content/**/*.geom
      ${CMAKE_CURRENT_SOURCE_DIR}/content/**/*.comp)

foreach (GLSL ${GLSL_SOURCE_FILES})
  get_filename_component (FILE_NAME ${GLSL} NAME)
  get_filename_component (FILE_PATH ${GLSL} PATH)
  get_filename_component (CONTENT_OUTPUT_PATH ${FILE_PATH} NAME)

  set (SPIRV "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/content/${CONTENT_OUTPUT_PATH}/${FILE_NAME}.spv")
  add_custom_command (
    OUTPUT  ${SPIRV}
    COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/content/${CONTENT_OUTPUT_PATH}"
    COMMAND ${GLSL_VALIDATOR} --aml --target-env vulkan1.0 -V ${GLSL} -o ${SPIRV}
    DEPENDS ${GLSL})
  list (APPEND SPIRV_BINARY_FILES ${SPIRV})
endforeach (GLSL)

add_custom_target (Shaders DEPENDS ${SPIRV_BINARY_FILES})

add_dependencies (skeletal-animation Shaders)

add_custom_command (TARGET skeletal-animation POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/content"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/content"
        "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/content"
)

# copy content files
add_custom_command (TARGET skeletal-animation POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_directory
                    ${CMAKE_CURRENT_SOURCE_DIR}/content ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/content)
