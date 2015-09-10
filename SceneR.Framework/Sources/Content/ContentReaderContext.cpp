// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/ContentReaderContext.hpp>

#include <Content/json11.hpp>
#include <Framework/Matrix.hpp>
#include <Framework/Quaternion.hpp>
#include <Framework/Vector2.hpp>
#include <Framework/Vector3.hpp>
#include <Framework/Vector4.hpp>
#include <Graphics/Accessor.hpp>
#include <Graphics/Buffer.hpp>
#include <Graphics/BufferView.hpp>
#include <Graphics/Effect.hpp>
#include <Graphics/GraphicsDevice.hpp>
#include <Graphics/Material.hpp>
#include <Graphics/ModelMesh.hpp>
#include <Graphics/Node.hpp>
#include <Graphics/SamplerState.hpp>
#include <Graphics/Program.hpp>
#include <Graphics/Shader.hpp>
#include <Graphics/Texture2D.hpp>
#include <System/Text/Encoding.hpp>

namespace SceneR
{
    namespace Content
    {
        using SceneR::Framework::Matrix;
        using SceneR::Framework::Quaternion;
        using SceneR::Framework::Vector2;
        using SceneR::Framework::Vector3;
        using SceneR::Framework::Vector4;
        using SceneR::Graphics::Accessor;
        using SceneR::Graphics::Buffer;
        using SceneR::Graphics::BufferView;
        using SceneR::Graphics::Effect;
        using SceneR::Graphics::GraphicsDevice;
        using SceneR::Graphics::Material;
        using SceneR::Graphics::ModelMesh;
        using SceneR::Graphics::Node;
        using SceneR::Graphics::Program;
        using SceneR::Graphics::SamplerState;
        using SceneR::Graphics::Shader;
        using SceneR::Graphics::Texture2D;
        using System::Text::Encoding;

        ContentReaderContext::ContentReaderContext(GraphicsDevice& graphicsDevice)
            : graphics_device (graphicsDevice)
            , accessors       ()
            , buffer_views    ()
            , effects         ()
            , materials       ()
        {
        }

        ContentReaderContext::~ContentReaderContext()
        {
        }

        template<>
        Matrix ContentReaderContext::convert(const std::vector<json11::Json>& values) const
        {
            Matrix matrix;

            #pragma unroll(16)
            for (int i = 0; i < 16; i++)
            {
                matrix.data[i] = values[i].number_value();
            }

            return Matrix::transpose(matrix);
        }

        template<>
        Quaternion ContentReaderContext::convert(const std::vector<json11::Json>& values) const
        {
            return { values[1].number_value()
                   , values[2].number_value()
                   , values[3].number_value()
                   , values[0].number_value(),};
        }

        template<>
        Vector2 ContentReaderContext::convert(const std::vector<json11::Json>& values) const
        {
            return Vector2 { values[0].number_value()
                          ,  values[1].number_value() };
        }

        template<>
        Vector3 ContentReaderContext::convert(const std::vector<json11::Json>& values) const
        {
            return Vector3 { values[0].number_value()
                          ,  values[1].number_value()
                          ,  values[2].number_value()};
        }

        template<>
        Vector4 ContentReaderContext::convert(const std::vector<json11::Json>& values) const
        {
            return Vector4 { values[0].number_value()
                          ,  values[1].number_value()
                          ,  values[2].number_value()
                          ,  values[3].number_value()};
        }

        template <>
        std::shared_ptr<Accessor> ContentReaderContext::find_object(const std::string& name) const
        {
            auto oname = Encoding::convert(name);
            auto it = find_if(accessors.begin()
                            , accessors.end()
                            , [&](std::shared_ptr<Accessor> accessor) -> bool
                {
                    return (accessor->name() == oname);
                });

            return ((it != accessors.end()) ? *it : nullptr);
        }

        template <>
        std::shared_ptr<Buffer> ContentReaderContext::find_object(const std::string& name) const
        {
            auto oname = Encoding::convert(name);
            auto it = find_if(buffers.begin()
                            , buffers.end()
                            , [&](std::shared_ptr<Buffer> buffer) -> bool
                {
                    return (buffer->name() == oname);
                });

            return ((it != buffers.end()) ? *it : nullptr);
        }

        template <>
        std::shared_ptr<BufferView> ContentReaderContext::find_object(const std::string& name) const
        {
            auto oname = Encoding::convert(name);
            auto it = find_if(buffer_views.begin()
                            , buffer_views.end()
                            , [&](std::shared_ptr<BufferView> bufferView) -> bool
                {
                    return (bufferView->name() == oname);
                });

            return ((it != buffer_views.end()) ? *it : nullptr);
        }

        template <>
        std::shared_ptr<Effect> ContentReaderContext::find_object(const std::string &name) const
        {
            auto oname = Encoding::convert(name);
            auto it = find_if(effects.begin()
                            , effects.end()
                            , [&](std::shared_ptr<Effect> effect) -> bool
                {
                    return (effect->name == oname);
                });

            return ((it != effects.end()) ? *it : nullptr);
        }

        template <>
        std::shared_ptr<Material> ContentReaderContext::find_object(const std::string& name) const
        {
            auto oname = Encoding::convert(name);
            auto it = find_if(materials.begin()
                            , materials.end()
                            , [&](std::shared_ptr<Material> material) -> bool
                {
                    return (material->name() == oname);
                });

            return ((it != materials.end()) ? *it : nullptr);
        }

        template <>
        std::shared_ptr<ModelMesh> ContentReaderContext::find_object(const std::string& name) const
        {
            auto oname = Encoding::convert(name);
            auto it = find_if(meshes.begin()
                            , meshes.end()
                            , [&](std::shared_ptr<ModelMesh> mesh) -> bool
                {
                    return (mesh->name() == oname);
                });

            return ((it != meshes.end()) ? *it : nullptr);
        }

        template <>
        std::shared_ptr<Node> ContentReaderContext::find_object(const std::string& name) const
        {
            auto oname = Encoding::convert(name);
            auto it = find_if(nodes.begin()
                            , nodes.end()
                            , [&](std::shared_ptr<Node> node) -> bool
                {
                    return (node->name == oname);
                });

            return ((it != nodes.end()) ? *it : nullptr);
        }

        template <>
        std::shared_ptr<Program> ContentReaderContext::find_object(const std::string& name) const
        {
            auto oname = Encoding::convert(name);
            auto it = find_if(programs.begin()
                            , programs.end()
                            , [&](std::shared_ptr<Program> program) -> bool
                {
                    return (program->name == oname);
                });

            return ((it != programs.end()) ? *it : nullptr);
        }

        template <>
        std::shared_ptr<SamplerState> ContentReaderContext::find_object(const std::string& name) const
        {
            auto oname = Encoding::convert(name);
            auto it = find_if(samplers.begin()
                            , samplers.end()
                            , [&](std::shared_ptr<SamplerState> sampler) -> bool
                {
                    return (sampler->name == oname);
                });

            return ((it != samplers.end()) ? *it : nullptr);
        }

        template <>
        std::shared_ptr<Shader> ContentReaderContext::find_object(const std::string& name) const
        {
            auto oname = Encoding::convert(name);
            auto it = find_if(shaders.begin()
                            , shaders.end()
                            , [&](std::shared_ptr<Shader> shader) -> bool
                {
                    return (shader->name() == oname);
                });

            return ((it != shaders.end()) ? *it : nullptr);
        }

        template <>
        std::shared_ptr<Texture2D> ContentReaderContext::find_object(const std::string& name) const
        {
            auto oname = Encoding::convert(name);
            auto it = find_if(textures.begin()
                            , textures.end()
                            , [&](std::shared_ptr<Texture2D> texture) -> bool
                {
                    return (texture->name == oname);
                });

            return ((it != textures.end()) ? *it : nullptr);
        }
    }
}
