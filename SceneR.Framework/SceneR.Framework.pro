#-------------------------------------------------
#
# Project created by QtCreator 2014-01-16T21:23:48
#
#-------------------------------------------------

QT       -= core
QT       -= gui

TARGET = SceneR.Framework
TEMPLATE = lib

CONFIG   += c++11

QMAKE_CXXFLAGS += -stdlib=libc++ -m64
QMAKE_LFLAGS += -stdlib=libc++ -m64

SOURCES += \
    Content/Readers/AnimationClipMapReader.cpp \
    Content/Readers/AnimationClipReader.cpp \
    Content/Readers/BasicEffectReader.cpp \
    Content/Readers/BoundingSphereReader.cpp \
    Content/Readers/IndexBufferReader.cpp \
    Content/Readers/Int32ListReader.cpp \
    Content/Readers/Int32Reader.cpp \
    Content/Readers/KeyframeListReader.cpp \
    Content/Readers/KeyframeReader.cpp \
    Content/Readers/MatrixListReader.cpp \
    Content/Readers/MatrixReader.cpp \
    Content/Readers/ModelReader.cpp \
    Content/Readers/SkinnedEffectReader.cpp \
    Content/Readers/SkinningDataReader.cpp \
    Content/Readers/StringReader.cpp \
    Content/Readers/Texture2DReader.cpp \
    Content/Readers/TimeSpanReader.cpp \
    Content/Readers/VertexBufferReader.cpp \
    Content/Readers/VertexDeclarationReader.cpp \
    Content/ContentManager.cpp \
    Content/ContentReader.cpp \
    Content/ContentTypeReaderManager.cpp \
    Framework/BoundingBox.cpp \
    Framework/BoundingFrustum.cpp \
    Framework/BoundingSphere.cpp \
    Framework/Color.cpp \
    Framework/Component.cpp \
    Framework/DrawableComponent.cpp \
    Framework/GraphicsDeviceManager.cpp \
    Framework/MathHelper.cpp \
    Framework/Matrix.cpp \
    Framework/Plane.cpp \
    Framework/Quaternion.cpp \
    Framework/Ray.cpp \
    Framework/Renderer.cpp \
    Framework/RendererTimer.cpp \
    Framework/RendererWindow.cpp \
    Framework/RenderTime.cpp \
    Framework/Vector2.cpp \
    Framework/Vector3.cpp \
    Framework/Vector4.cpp \
    Graphics/AnimatedModel.cpp \
    Graphics/AnimationClip.cpp \
    Graphics/AnimationPlayer.cpp \
    Graphics/BasicEffect.cpp \
    Graphics/BlendState.cpp \
    Graphics/BufferObject.cpp \
    Graphics/DepthStencilState.cpp \
    Graphics/DirectionalLight.cpp \
    Graphics/DisplayMode.cpp \
    Graphics/Effect.cpp \
    Graphics/EffectParameter.cpp \
    Graphics/EffectParameterCollection.cpp \
    Graphics/GraphicsAdapter.cpp \
    Graphics/GraphicsDevice.cpp \
    Graphics/GraphicsResource.cpp \
    Graphics/IndexBuffer.cpp \
    Graphics/Keyframe.cpp \
    Graphics/Model.cpp \
    Graphics/ModelBone.cpp \
    Graphics/ModelMesh.cpp \
    Graphics/ModelMeshPart.cpp \
    Graphics/PresentationParameters.cpp \
    Graphics/RasterizerState.cpp \
    Graphics/SamplerState.cpp \
    Graphics/Shader.cpp \
    Graphics/ShaderProgram.cpp \
    Graphics/SkinnedEffect.cpp \
    Graphics/SkinningData.cpp \
    Graphics/Texture.cpp \
    Graphics/Texture2D.cpp \
    Graphics/TextureObject.cpp \
    Graphics/UniformBufferObject.cpp \
    Graphics/VertexArrayObject.cpp \
    Graphics/VertexBuffer.cpp \
    Graphics/VertexDeclaration.cpp \
    Graphics/VertexElement.cpp \
    Graphics/VertexPositionColor.cpp \
    Graphics/VertexPositionColorTexture.cpp \
    Graphics/VertexPositionNormalTexture.cpp \
    Graphics/Viewport.cpp \
    System/TimeSpan.cpp \
    System/IO/BinaryReader.cpp \
    System/IO/FileStream.cpp \
    System/IO/MemoryStream.cpp \
    System/Text/Decoder.cpp \
    System/Text/Encoder.cpp \
    System/Text/Encoding.cpp \
    System/Text/UTF8Decoder.cpp \
    System/Text/UTF8Encoder.cpp \
    System/Text/UTF8Encoding.cpp \
    Content/SharedResourceAction.cpp

HEADERS += \
    Content/Readers/AnimationClipMapReader.hpp \
    Content/Readers/AnimationClipReader.hpp \
    Content/Readers/BasicEffectReader.hpp \
    Content/Readers/BoundingSphereReader.hpp \
    Content/Readers/IndexBufferReader.hpp \
    Content/Readers/Int32ListReader.hpp \
    Content/Readers/Int32Reader.hpp \
    Content/Readers/KeyframeListReader.hpp \
    Content/Readers/KeyframeReader.hpp \
    Content/Readers/MatrixListReader.hpp \
    Content/Readers/MatrixReader.hpp \
    Content/Readers/ModelReader.hpp \
    Content/Readers/SkinnedEffectReader.hpp \
    Content/Readers/SkinningDataReader.hpp \
    Content/Readers/StringReader.hpp \
    Content/Readers/Texture2DReader.hpp \
    Content/Readers/TimeSpanReader.hpp \
    Content/Readers/VertexBufferReader.hpp \
    Content/Readers/VertexDeclarationReader.hpp \
    Content/ContentLoadException.hpp \
    Content/ContentManager.hpp \
    Content/ContentReader.hpp \
    Content/ContentTypeReader.hpp \
    Content/ContentTypeReaderManager.hpp \
    Framework/BoundingBox.hpp \
    Framework/BoundingFrustrum.hpp \
    Framework/BoundingSphere.hpp \
    Framework/Color.hpp \
    Framework/Component.hpp \
    Framework/ContainmentType.hpp \
    Framework/DrawableComponent.hpp \
    Framework/GraphicsDeviceManager.hpp \
    Framework/IComponent.hpp \
    Framework/IDrawable.hpp \
    Framework/IGraphicsDeviceManager.hpp \
    Framework/IUpdateable.hpp \
    Framework/MathHelper.hpp \
    Framework/Matrix.hpp \
    Framework/Plane.hpp \
    Framework/PlaneIntersectionType.hpp \
    Framework/PresentInterval.hpp \
    Framework/Quaternion.hpp \
    Framework/Ray.hpp \
    Framework/Renderer.hpp \
    Framework/RendererServiceContainer.hpp \
    Framework/RendererTimer.hpp \
    Framework/RendererWindow.hpp \
    Framework/RenderTime.hpp \
    Framework/Vector2.hpp \
    Framework/Vector3.hpp \
    Framework/Vector4.hpp \
    Graphics/AnimatedModel.hpp \
    Graphics/AnimationClip.hpp \
    Graphics/AnimationPlayer.hpp \
    Graphics/BasicEffect.hpp \
    Graphics/Blend.hpp \
    Graphics/BlendFunction.hpp \
    Graphics/BlendState.hpp \
    Graphics/BufferObject.hpp \
    Graphics/BufferTarget.hpp \
    Graphics/BufferUsage.hpp \
    Graphics/ColorWriteChannels.hpp \
    Graphics/CompareFunction.hpp \
    Graphics/CullMode.hpp \
    Graphics/DepthStencilState.hpp \
    Graphics/DirectionalLight.hpp \
    Graphics/DisplayMode.hpp \
    Graphics/Effect.hpp \
    Graphics/EffectParameter.hpp \
    Graphics/EffectParameterClass.hpp \
    Graphics/EffectParameterCollection.hpp \
    Graphics/EffectParameterType.hpp \
    Graphics/FillMode.hpp \
    Graphics/GraphicsAdapter.hpp \
    Graphics/GraphicsDevice.hpp \
    Graphics/GraphicsProfile.hpp \
    Graphics/GraphicsResource.hpp \
    Graphics/IEffectFog.hpp \
    Graphics/IEffectLights.hpp \
    Graphics/IEffectMatrices.hpp \
    Graphics/IGraphicsDeviceService.hpp \
    Graphics/IndexBuffer.hpp \
    Graphics/IndexElementSize.hpp \
    Graphics/Keyframe.hpp \
    Graphics/Model.hpp \
    Graphics/ModelBone.hpp \
    Graphics/ModelMesh.hpp \
    Graphics/ModelMeshPart.hpp \
    Graphics/PresentationParameters.hpp \
    Graphics/PrimitiveType.hpp \
    Graphics/RasterizerState.hpp \
    Graphics/SamplerState.hpp \
    Graphics/Shader.hpp \
    Graphics/ShaderProgram.hpp \
    Graphics/ShaderType.hpp \
    Graphics/SkinnedEffect.hpp \
    Graphics/SkinningData.hpp \
    Graphics/StencilOperation.hpp \
    Graphics/SurfaceFormat.hpp \
    Graphics/Texture.hpp \
    Graphics/Texture2D.hpp \
    Graphics/TextureAddressMode.hpp \
    Graphics/TextureFilter.hpp \
    Graphics/TextureObject.hpp \
    Graphics/TextureTarget.hpp \
    Graphics/UniformBufferObject.hpp \
    Graphics/VertexArrayObject.hpp \
    Graphics/VertexBuffer.hpp \
    Graphics/VertexDeclaration.hpp \
    Graphics/VertexElement.hpp \
    Graphics/VertexElementFormat.hpp \
    Graphics/VertexElementUsage.hpp \
    Graphics/VertexPositionColor.hpp \
    Graphics/VertexPositionColorTexture.hpp \
    Graphics/VertexPositionNormalTexture.hpp \
    Graphics/Viewport.hpp \
    System/Graphics/Platform.hpp \
    System/IO/BinaryReader.hpp \
    System/IO/File.hpp \
    System/IO/FileStream.hpp \
    System/IO/MemoryStream.hpp \
    System/IO/Path.hpp \
    System/IO/Stream.hpp \
    System/Core.hpp \
    System/Pointer.hpp \
    System/TimeSpan.hpp \
    System/Text/Decoder.hpp \
    System/Text/Encoder.hpp \
    System/Text/Encoding.hpp \
    System/Text/UTF8Decoder.hpp \
    System/Text/UTF8Encoder.hpp \
    System/Text/UTF8Encoding.hpp

unix {
    target.path = /usr/lib
    INSTALLS += target
}

unix|win32: LIBS += -lpthread

unix|win32: LIBS += -L$$/usr/local/lib -lglfw

unix|win32: LIBS += -L$$PWD/../../regal/lib/linux/ -lRegal

DEPENDPATH += $$PWD/../../regal/include
INCLUDEPATH += $$PWD/../../regal/include \
               $$PWD/Headers

VPATH += $$PWD/Headers \
         $$PWD/Sources
