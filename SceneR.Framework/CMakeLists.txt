cmake_minimum_required(VERSION 3.2.2)
project(SceneR_Framework)
enable_language(CXX)

set (CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/installed" CACHE PATH "default install path" FORCE)

# enable c++11 & clang standard library
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++14 -stdlib=libc++ -g3 -O0 -Wall -Wextra -Wno-unused-parameter")

# -Weverything -Wno-reserved-id-macro -Wno-shadow -Wno-c++98-compat -Wno-padded -Wno-unused-parameter -Wno-nested-anon-types -Wno-gnu-anonymous-struct

# Reconfigure final output directory
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE})
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE})
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE})

message (STATUS "Ouput Directory: " ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

# include directories
include_directories(Headers)

# PkgConfig
find_package(PkgConfig REQUIRED)

# pthread
find_package(Threads REQUIRED)

# OpenGL
find_package(OpenGL REQUIRED)

# glew
# find_package(GLEW REQUIRED)

# glfw
pkg_search_module(GLFW REQUIRED glfw3)

# Regal
link_directories(../../regal/lib/linux/)

# header files
set(HEADER_FILES
    Headers/Content/Readers/AccessorReader.hpp
    Headers/Content/Readers/BufferReader.hpp
    Headers/Content/Readers/BufferViewReader.hpp
    Headers/Content/Readers/ExternalReferenceReader.hpp
    Headers/Content/Readers/MaterialReader.hpp
    Headers/Content/Readers/MeshReader.hpp
    Headers/Content/Readers/NodeReader.hpp
    Headers/Content/Readers/ProgramReader.hpp
    Headers/Content/Readers/SamplerReader.hpp
    Headers/Content/Readers/ShaderReader.hpp
    Headers/Content/Readers/TechniqueReader.hpp
    Headers/Content/Readers/TextureReader.hpp
    Headers/Content/json11.hpp
    Headers/Content/ContentResourceManager.hpp
    Headers/Content/ContentLoadException.hpp
    Headers/Content/ContentManager.hpp
    Headers/Content/ContentReader.hpp
    Headers/Content/ContentTypeReader.hpp
    Headers/Framework/BoundingBox.hpp
    Headers/Framework/BoundingFrustrum.hpp
    Headers/Framework/BoundingSphere.hpp
    Headers/Framework/Color.hpp
    Headers/Framework/Component.hpp
    Headers/Framework/ContainmentType.hpp
    Headers/Framework/DrawableComponent.hpp
    Headers/Framework/GraphicsDeviceManager.hpp
    Headers/Framework/IComponent.hpp
    Headers/Framework/IDrawable.hpp
    Headers/Framework/IGraphicsDeviceManager.hpp
    Headers/Framework/IUpdateable.hpp
    Headers/Framework/Matrix.hpp
    Headers/Framework/Plane.hpp
    Headers/Framework/PlaneIntersectionType.hpp
    Headers/Framework/PresentInterval.hpp
    Headers/Framework/Quaternion.hpp
    Headers/Framework/Ray.hpp
    Headers/Framework/Renderer.hpp
    Headers/Framework/RendererServiceContainer.hpp
    Headers/Framework/RendererTimer.hpp
    Headers/Framework/RendererWindow.hpp
    Headers/Framework/RenderTime.hpp
    Headers/Framework/Vector2.hpp
    Headers/Framework/Vector3.hpp
    Headers/Framework/Vector4.hpp
    Headers/Graphics/Accessor.hpp
    Headers/Graphics/AttributeType.hpp
    Headers/Graphics/Blend.hpp
    Headers/Graphics/BlendFunction.hpp
    Headers/Graphics/BlendState.hpp
    Headers/Graphics/Buffer.hpp
    Headers/Graphics/BufferObject.hpp
    Headers/Graphics/BufferTarget.hpp
    Headers/Graphics/BufferUsage.hpp
    Headers/Graphics/BufferView.hpp
    Headers/Graphics/BufferType.hpp
    Headers/Graphics/ColorWriteChannels.hpp
    Headers/Graphics/ComponentType.hpp
    Headers/Graphics/CompareFunction.hpp
    Headers/Graphics/CullMode.hpp
    Headers/Graphics/DepthStencilState.hpp
    Headers/Graphics/DirectionalLight.hpp
    Headers/Graphics/DisplayMode.hpp
    Headers/Graphics/EffectTechnique.hpp
    Headers/Graphics/EffectDirtyFlags.hpp
    Headers/Graphics/EffectHelpers.hpp
    Headers/Graphics/EffectPass.hpp
    Headers/Graphics/EffectPassStates.hpp
    Headers/Graphics/EffectParameter.hpp
    Headers/Graphics/EffectParameterClass.hpp
    Headers/Graphics/EffectParameterType.hpp
    Headers/Graphics/FillMode.hpp
    Headers/Graphics/GraphicsAdapter.hpp
    Headers/Graphics/GraphicsDevice.hpp
    Headers/Graphics/GraphicsProfile.hpp
    Headers/Graphics/GraphicsResource.hpp
    Headers/Graphics/IEffectFog.hpp
    Headers/Graphics/IEffectLights.hpp
    Headers/Graphics/IEffectMatrices.hpp
    Headers/Graphics/IGraphicsDeviceService.hpp
    Headers/Graphics/IndexBuffer.hpp
    Headers/Graphics/InstanceSkin.hpp
    Headers/Graphics/EffectMaterial.hpp
    Headers/Graphics/Model.hpp
    Headers/Graphics/ModelBone.hpp
    Headers/Graphics/ModelMesh.hpp
    Headers/Graphics/ModelMeshPart.hpp
    Headers/Graphics/Node.hpp
    Headers/Graphics/PresentationParameters.hpp
    Headers/Graphics/PrimitiveType.hpp
    Headers/Graphics/Program.hpp
    Headers/Graphics/RasterizerState.hpp
    Headers/Graphics/RenderingStateType.hpp
    Headers/Graphics/SamplerState.hpp
    Headers/Graphics/Shader.hpp
    Headers/Graphics/ShaderType.hpp
    Headers/Graphics/StencilOperation.hpp
    Headers/Graphics/SurfaceFormat.hpp
    Headers/Graphics/Texture.hpp
    Headers/Graphics/Texture2D.hpp
    Headers/Graphics/TextureAddressMode.hpp
    Headers/Graphics/TextureFilter.hpp
    Headers/Graphics/TextureObject.hpp
    Headers/Graphics/TextureTarget.hpp
    Headers/Graphics/UniformBufferObject.hpp
    Headers/Graphics/VertexArrayObject.hpp
    Headers/Graphics/VertexBuffer.hpp
    Headers/Graphics/VertexDeclaration.hpp
    Headers/Graphics/VertexElement.hpp
    Headers/Graphics/VertexElementFormat.hpp
    Headers/Graphics/VertexElementUsage.hpp
    Headers/Graphics/VertexPositionColor.hpp
    Headers/Graphics/VertexPositionColorTexture.hpp
    Headers/Graphics/VertexPositionNormalTexture.hpp
    Headers/Graphics/Viewport.hpp
    Headers/Input/Buttons.hpp
    Headers/Input/ButtonState.hpp
    Headers/Input/Keys.hpp
    Headers/Input/KeyState.hpp
    Headers/Input/Keyboard.hpp
    Headers/Input/KeyboardState.hpp
    Headers/Input/Mouse.hpp
    Headers/Input/MouseState.hpp
    Headers/System/IDisposable.hpp
    Headers/System/Math.hpp
    Headers/System/TimeSpan.hpp
    Headers/System/Graphics/Platform.hpp
    Headers/System/IO/BinaryReader.hpp
    Headers/System/IO/File.hpp
    Headers/System/IO/FileStream.hpp
    Headers/System/IO/MemoryStream.hpp
    Headers/System/IO/Path.hpp
    Headers/System/IO/Stream.hpp
    Headers/System/Text/Decoder.hpp
    Headers/System/Text/Encoder.hpp
    Headers/System/Text/Encoding.hpp
    Headers/System/Text/UTF8Decoder.hpp
    Headers/System/Text/UTF8Encoder.hpp
    Headers/System/Text/UTF8Encoding.hpp)

# source files
set(SOURCE_FILES
    Sources/Content/Readers/AccessorReader.cpp
    Sources/Content/Readers/BufferReader.cpp
    Sources/Content/Readers/BufferViewReader.cpp
    Sources/Content/Readers/ExternalReferenceReader.cpp
    Sources/Content/Readers/MaterialReader.cpp
    Sources/Content/Readers/MeshReader.cpp
    Sources/Content/Readers/NodeReader.cpp
    Sources/Content/Readers/ProgramReader.cpp
    Sources/Content/Readers/SamplerReader.cpp
    Sources/Content/Readers/ShaderReader.cpp
    Sources/Content/Readers/TechniqueReader.cpp
    Sources/Content/Readers/TextureReader.cpp
    Sources/Content/ContentLoadException.cpp
    Sources/Content/ContentManager.cpp
    Sources/Content/ContentReader.cpp
    Sources/Content/json11.cpp
    Sources/Framework/BoundingBox.cpp
    Sources/Framework/BoundingFrustrum.cpp
    Sources/Framework/BoundingSphere.cpp
    Sources/Framework/Color.cpp
    Sources/Framework/Component.cpp
    Sources/Framework/DrawableComponent.cpp
    Sources/Framework/GraphicsDeviceManager.cpp
    Sources/Framework/IComponent.cpp
    Sources/Framework/IDrawable.cpp
    Sources/Framework/IUpdateable.cpp
    Sources/Framework/IGraphicsDeviceManager.cpp
    Sources/Framework/Matrix.cpp
    Sources/Framework/Plane.cpp
    Sources/Framework/Quaternion.cpp
    Sources/Framework/Ray.cpp
    Sources/Framework/Renderer.cpp
    Sources/Framework/RendererTimer.cpp
    Sources/Framework/RendererWindow.cpp
    Sources/Framework/RenderTime.cpp
    Sources/Framework/Vector2.cpp
    Sources/Framework/Vector3.cpp
    Sources/Framework/Vector4.cpp
    Sources/Graphics/Accessor.cpp
    Sources/Graphics/Buffer.cpp
    Sources/Graphics/BufferObject.cpp
    Sources/Graphics/BlendState.cpp
    Sources/Graphics/BufferView.cpp
    Sources/Graphics/DepthStencilState.cpp
    Sources/Graphics/DirectionalLight.cpp
    Sources/Graphics/DisplayMode.cpp
    Sources/Graphics/EffectTechnique.cpp
    Sources/Graphics/EffectHelpers.cpp
    Sources/Graphics/EffectParameter.cpp
    Sources/Graphics/EffectPass.cpp
    Sources/Graphics/GraphicsAdapter.cpp
    Sources/Graphics/GraphicsDevice.cpp
    Sources/Graphics/GraphicsResource.cpp
    Sources/Graphics/IEffectFog.cpp
    Sources/Graphics/IEffectLights.cpp
    Sources/Graphics/IEffectMatrices.cpp
    Sources/Graphics/IGraphicsDeviceService.cpp
    Sources/Graphics/IndexBuffer.cpp
    Sources/Graphics/InstanceSkin.cpp
    Sources/Graphics/EffectMaterial.cpp
    Sources/Graphics/Model.cpp
    Sources/Graphics/ModelBone.cpp
    Sources/Graphics/ModelMesh.cpp
    Sources/Graphics/ModelMeshPart.cpp
    Sources/Graphics/Node.cpp
    Sources/Graphics/PresentationParameters.cpp
    Sources/Graphics/Program.cpp
    Sources/Graphics/RasterizerState.cpp
    Sources/Graphics/SamplerState.cpp
    Sources/Graphics/Shader.cpp
    Sources/Graphics/Texture.cpp
    Sources/Graphics/Texture2D.cpp
    Sources/Graphics/TextureObject.cpp
    Sources/Graphics/UniformBufferObject.cpp
    Sources/Graphics/VertexArrayObject.cpp
    Sources/Graphics/VertexBuffer.cpp
    Sources/Graphics/VertexDeclaration.cpp
    Sources/Graphics/VertexElement.cpp
    Sources/Graphics/VertexPositionColor.cpp
    Sources/Graphics/VertexPositionColorTexture.cpp
    Sources/Graphics/VertexPositionNormalTexture.cpp
    Sources/Graphics/Viewport.cpp
    Sources/Input/Keyboard.cpp
    Sources/Input/KeyboardState.cpp
    Sources/Input/Mouse.cpp
    Sources/Input/MouseState.cpp
    Sources/System/IDisposable.cpp
    Sources/System/Math.cpp
    Sources/System/TimeSpan.cpp
    Sources/System/IO/BinaryReader.cpp
    Sources/System/IO/FileStream.cpp
    Sources/System/IO/MemoryStream.cpp
    Sources/System/IO/Stream.cpp
    Sources/System/Text/Decoder.cpp
    Sources/System/Text/Encoder.cpp
    Sources/System/Text/Encoding.cpp
    Sources/System/Text/UTF8Decoder.cpp
    Sources/System/Text/UTF8Encoder.cpp
    Sources/System/Text/UTF8Encoding.cpp)

#set_source_files_properties(Headers/Graphics/Resources.hpp PROPERTIES GENERATED TRUE)
#set_source_files_properties(Sources/Graphics/Resources.cpp PROPERTIES GENERATED TRUE)

# resource script file
set(GENERATE_RESOURCES_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/generate_resources.cmake)

# add script files ( so they appear in the IDE )
add_custom_target(SCRIPT_FILES SOURCES ${GENERATE_RESOURCES_SCRIPT})

# add content_manager files
add_custom_target(CONTENT_FILES SOURCES
                  Resources/BasicEffect.frag
                  Resources/BasicEffect.glsl
                  Resources/BasicEffect.vert
                  Resources/Common.glsl
                  Resources/Lighting.glsl
                  Resources/SkinnedEffect.vert
                  Resources/SkinnedEffect.glsl
                  Resources/SkinnedEffect.frag
                  Resources/Structures.glsl)

# generate resource sources files before build
#add_custom_target(RESOURCES_GENERATION
#                  COMMAND ${CMAKE_COMMAND}
#                       -D ROOT_DIRECTORY=${CMAKE_CURRENT_SOURCE_DIR}
#                       -P ${GENERATE_RESOURCES_SCRIPT}
#                  DEPENDS CONTENT_FILES
#                  COMMENT "generating resource files")

# library output
add_library(SceneR_Framework SHARED ${HEADER_FILES} ${SOURCE_FILES})

# target dependencies
#add_dependencies(SceneR_Framework RESOURCES_GENERATION)

# enable 64 bit build
set_target_properties(SceneR_Framework PROPERTIES COMPILE_FLAGS -m64 LINK_FLAGS -m64)

# target include directories
target_include_directories(SceneR_Framework
                           PRIVATE ${OPENGL_INCLUDE_DIRS}
                           PRIVATE ../../regal/include
                           # PRIVATE ${GLEW_INCLUDE_DIRS}
                           PRIVATE ${GLFW_INCLUDE_DIRS})

# target links
target_link_libraries(SceneR_Framework
                      c++abi
                      pthread
                      ${OPENGL_LIBRARIES}
                      #${GLEW_LIBRARIES}
                      Regal
                      ${GLFW_LIBRARIES})

# install target
install(TARGETS SceneR_Framework
        RUNTIME DESTINATION bin COMPONENT libraries
        LIBRARY DESTINATION lib COMPONENT libraries
        ARCHIVE DESTINATION lib/static COMPONENT libraries)

# install header files
install(DIRECTORY Headers/ DESTINATION include
        FILES_MATCHING PATTERN "*.hpp")
