project (SceneR_Framework)

# include directories
include_directories (${JSON11_INCLUDE_DIRS}
                     ${GSL_INCLUDE_DIRS}
                     ${OPENGL_INCLUDE_DIRS}
                     ${GLEW_INCLUDE_DIRS}
                     ${GLFW_INCLUDE_DIRS}
                     Headers)

# PkgConfig
find_package (PkgConfig REQUIRED)

# pthread
find_package (Threads REQUIRED)

# OpenGL
find_package (OpenGL REQUIRED)

# glfw
pkg_search_module (GLFW REQUIRED glfw3)

# glew
link_directories (${GLEW_LIB_DIRS})

# header files
set (HEADER_FILES
     Headers/Content/Readers/AccessorReader.hpp
     Headers/Content/Readers/AnimationReader.hpp
     Headers/Content/Readers/BufferReader.hpp
     Headers/Content/Readers/BufferViewReader.hpp
     Headers/Content/Readers/ImageReader.hpp
     Headers/Content/Readers/ModelMeshReader.hpp
     Headers/Content/Readers/NodeReader.hpp
     Headers/Content/Readers/ProgramReader.hpp
     Headers/Content/Readers/SamplerReader.hpp
     Headers/Content/Readers/ShaderIncludeReader.hpp
     Headers/Content/Readers/ShaderReader.hpp
     Headers/Content/Readers/TechniqueReader.hpp
     Headers/Content/Readers/TextureReader.hpp
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
     Headers/Graphics/Animation.hpp
     Headers/Graphics/AttributeType.hpp
     Headers/Graphics/Blend.hpp
     Headers/Graphics/BlendFunction.hpp
     Headers/Graphics/BlendState.hpp
     Headers/Graphics/Buffer.hpp
     Headers/Graphics/BufferObject.hpp
     Headers/Graphics/BufferTarget.hpp
     Headers/Graphics/BufferUsage.hpp
     Headers/Graphics/BufferView.hpp
     Headers/Graphics/ColorWriteChannels.hpp
     Headers/Graphics/ComponentType.hpp
     Headers/Graphics/CompareFunction.hpp
     Headers/Graphics/CullMode.hpp
     Headers/Graphics/DepthStencilState.hpp
     Headers/Graphics/DirectionalLight.hpp
     Headers/Graphics/DisplayMode.hpp
     Headers/Graphics/EffectTechnique.hpp
     Headers/Graphics/EffectDirtyFlags.hpp
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
     Headers/Graphics/Keyframe.hpp
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
     Headers/Graphics/ShaderInclude.hpp
     Headers/Graphics/ShaderType.hpp
     Headers/Graphics/Skeleton.hpp
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
     Headers/System/Text/UTF8Encoder.hpp
     Headers/System/Text/UTF8Decoder.hpp
     Headers/System/Text/UTF8Encoding.hpp
     Headers/Texture/DdsCaps.hpp
     Headers/Texture/DdsCaps2.hpp
     Headers/Texture/DdsFourCC.hpp
     Headers/Texture/DdsHeaderFlags.hpp
     Headers/Texture/DdsPixelFormatFlags.hpp
     Headers/Texture/DdsPixelFormat.hpp
     Headers/Texture/Dds.hpp
     Headers/Texture/Surface.hpp
     Headers/Texture/SurfaceMipmap.hpp)

# source files
set (SOURCE_FILES
     Sources/Content/Readers/AccessorReader.cpp
     Sources/Content/Readers/AnimationReader.cpp
     Sources/Content/Readers/BufferReader.cpp
     Sources/Content/Readers/BufferViewReader.cpp
     Sources/Content/Readers/ImageReader.cpp
     Sources/Content/Readers/ModelMeshReader.cpp
     Sources/Content/Readers/NodeReader.cpp
     Sources/Content/Readers/ProgramReader.cpp
     Sources/Content/Readers/SamplerReader.cpp
     Sources/Content/Readers/ShaderIncludeReader.cpp
     Sources/Content/Readers/ShaderReader.cpp
     Sources/Content/Readers/TechniqueReader.cpp
     Sources/Content/Readers/TextureReader.cpp
     Sources/Content/ContentLoadException.cpp
     Sources/Content/ContentManager.cpp
     Sources/Content/ContentReader.cpp
     Sources/Framework/BoundingBox.cpp
     Sources/Framework/BoundingFrustrum.cpp
     Sources/Framework/BoundingSphere.cpp
     Sources/Framework/Color.cpp
     Sources/Framework/Component.cpp
     Sources/Framework/DrawableComponent.cpp
     Sources/Framework/GraphicsDeviceManager.cpp
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
     Sources/Graphics/Animation.cpp
     Sources/Graphics/Buffer.cpp
     Sources/Graphics/BufferObject.cpp
     Sources/Graphics/BlendState.cpp
     Sources/Graphics/BufferView.cpp
     Sources/Graphics/DepthStencilState.cpp
     Sources/Graphics/DirectionalLight.cpp
     Sources/Graphics/DisplayMode.cpp
     Sources/Graphics/EffectTechnique.cpp
     Sources/Graphics/EffectParameter.cpp
     Sources/Graphics/EffectPass.cpp
     Sources/Graphics/GraphicsAdapter.cpp
     Sources/Graphics/GraphicsDevice.cpp
     Sources/Graphics/GraphicsResource.cpp
     Sources/Graphics/IndexBuffer.cpp
     Sources/Graphics/Keyframe.cpp
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
     Sources/Graphics/ShaderInclude.cpp
     Sources/Graphics/Skeleton.cpp
     Sources/Graphics/Texture.cpp
     Sources/Graphics/Texture2D.cpp
     Sources/Graphics/TextureObject.cpp
     Sources/Graphics/UniformBufferObject.cpp
     Sources/Graphics/VertexArrayObject.cpp
     Sources/Graphics/VertexBuffer.cpp
     Sources/Graphics/VertexDeclaration.cpp
     Sources/Graphics/VertexElement.cpp
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
     Sources/System/Text/Encoder.cpp
     Sources/System/Text/Decoder.cpp
     Sources/System/Text/Encoding.cpp
     Sources/System/Text/UTF8Decoder.cpp
     Sources/System/Text/UTF8Encoder.cpp
     Sources/System/Text/UTF8Encoding.cpp
     Sources/Texture/Surface.cpp
     Sources/Texture/SurfaceMipmap.cpp)

# library output
add_library (SceneR_Framework SHARED ${HEADER_FILES} ${SOURCE_FILES})

# enable 64 bit build
set_target_properties (SceneR_Framework PROPERTIES COMPILE_FLAGS -m64 LINK_FLAGS -m64 -nostdlib -nodefaultlibs)

# target sources
target_sources (SceneR_Framework PRIVATE ${JSON11_SOURCE_DIRS}/json11.cpp)

# target links
target_link_libraries (SceneR_Framework
                       c++abi
                       pthread
                       X11
                       Xi
                       Xrandr
                       Xxf86vm
                       Xinerama
                       Xcursor
                       rt
                       m
                       ${OPENGL_LIBRARIES}
                       ${GLEW_LIBRARIES}
                       ${GLFW_LIBRARIES})