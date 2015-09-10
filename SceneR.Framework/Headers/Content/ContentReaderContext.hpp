// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef CONTENT_CONTENTREADERCONTEXT_HPP
#define CONTENT_CONTENTREADERCONTEXT_HPP

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace json11
{
    class Json;
}

namespace SceneR
{
    namespace Graphics
    {
        class Accessor;
        class Buffer;
        class BufferView;
        class Effect;
        class GraphicsDevice;
        class Material;
        class Model;
        class ModelMesh;
        class Node;
        class Program;
        class SamplerState;
        class Shader;
        class Texture2D;
    }
}

namespace SceneR
{
    namespace Content
    {
        class ContentReader;

        class ContentReaderContext
        {
        public:
            ContentReaderContext(SceneR::Graphics::GraphicsDevice& graphicsDevice);
            ~ContentReaderContext();

        public:
            template <typename T>
            std::shared_ptr<T> find_object(const std::string& name) const;

            template <typename T>
            T convert(const std::vector<json11::Json>& values) const;

        public:
            ContentReader*                                               content_reader;
            SceneR::Graphics::GraphicsDevice&                            graphics_device;
            std::shared_ptr<SceneR::Graphics::Model>                     model;

            std::vector<std::shared_ptr<SceneR::Graphics::Accessor>>     accessors;
            std::vector<std::shared_ptr<SceneR::Graphics::Buffer>>       buffers;
            std::vector<std::shared_ptr<SceneR::Graphics::BufferView>>   buffer_views;
            std::vector<std::shared_ptr<SceneR::Graphics::Effect>>       effects;
            std::map<std::string, std::vector<std::uint8_t>>             images;
            std::vector<std::shared_ptr<SceneR::Graphics::Material>>     materials;
            std::vector<std::shared_ptr<SceneR::Graphics::ModelMesh>>    meshes;
            std::vector<std::shared_ptr<SceneR::Graphics::Node>>         nodes;
            std::vector<std::shared_ptr<SceneR::Graphics::Program>>      programs;
            std::vector<std::shared_ptr<SceneR::Graphics::SamplerState>> samplers;
            std::vector<std::shared_ptr<SceneR::Graphics::Shader>>       shaders;
            std::vector<std::shared_ptr<SceneR::Graphics::Texture2D>>    textures;
        };
    }
}

#endif // CONTENT_CONTENTREADERCONTEXT_HPP
