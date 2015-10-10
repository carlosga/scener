// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef CONTENT_CONTENTREADER_HPP
#define CONTENT_CONTENTREADER_HPP

#include <algorithm>
#include <cstdint>
#include <map>
#include <memory>
#include <vector>
#include <string>

#include <gsl.h>
#include <json11.hpp>

#include <Content/ContentTypeReader.hpp>
#include <Framework/Matrix.hpp>
#include <Framework/Quaternion.hpp>
#include <Framework/Vector2.hpp>
#include <Framework/Vector3.hpp>
#include <Framework/Vector4.hpp>
#include <Graphics/ModelBone.hpp>
#include <Graphics/Node.hpp>
#include <System/IO/BinaryReader.hpp>
#include <System/IO/Stream.hpp>

namespace SceneR
{
    namespace Graphics
    {
        class Accessor;
        class Buffer;
        class BufferView;
        class EffectTechnique;
        class Model;
        class ModelMesh;
        class Node;
        class Program;
        class SamplerState;
        class Shader;
        class ShaderInclude;
        class Texture2D;
    }

    namespace Texture
    {
        class Surface;
    }

    namespace Content
    {
        class ContentManager;

       /**
         * Reads application content_manager from disk
         */
        class ContentReader final
        {
        public:
            /**
             * Initializes a new instance of the ContentReader.
             * @param assetName the name of the asset to be readed.
             * @param contentManager the content_manager that owns this ContentReader.
             * @param stream the base stream.
             */
            ContentReader(const std::string&             assetName
                        , gsl::not_null<ContentManager*> contentManager
                        , System::IO::Stream&            stream);

            /**
             * Releases all resources used by the current instance of the ContentReader class.
             */
            ~ContentReader() = default;

        public:
            /**
             * Gets the name of the asset currently being read by this ContentReader.
             */
            const std::string& asset_name() const noexcept;

            /**
             * Gets the content manager that owns this ContentReader.
             */
            ContentManager* content_manager() const noexcept;

         public:
            /**
             * Reads the contexts of the current asset.
             * @return The contexts of the current asset.
             */
            std::shared_ptr<SceneR::Graphics::Model> read_asset();

            /**
             * Reads the header from the current stream.
             */
            bool read_header();

            /**
             * Reads a single object from the current stream.
             */
            template<typename T>
            inline std::shared_ptr<T> read_object(const std::string& rootKey, const std::string& key)
            {
                return read_object<T>({ key, _root[rootKey][key] });
            }

            /**
             * Reads a single object from the current stream.
             */
            template<typename T>
            inline std::shared_ptr<T> read_object(const std::pair<std::string, json11::Json>& source)
            {
                auto instance = get_object<T>(source.first);
                if (instance != nullptr)
                {
                    return instance;
                }

                std::shared_ptr<T> object = read_object_instance<T>(source);

                cache_object<T>(source.first, object);

                return object;
            }

            template<typename T>
            inline std::shared_ptr<T> read_object_instance(const std::string& rootKey, const std::string& key)
            {
                return read_object_instance<T>({ key, _root[rootKey][key] });
            }

            template<typename T>
            inline std::shared_ptr<T> read_object_instance(const std::pair<std::string, json11::Json>& source)
            {
                ContentTypeReader<T> reader;
                std::shared_ptr<T>   object = reader.read(this, source);

                return object;
            }

            inline std::shared_ptr<SceneR::Graphics::Node> find_joint_node(const std::string& jointName) const
            {
                for (const auto node : _nodes)
                {
                    if (node.second.get())
                    {
                        auto joint = node.second->joint;

                        if (joint.get() && joint->name() == jointName)
                        {
                            return node.second;
                        }
                    }
                }

                return nullptr;
            }

            /**
             * Reads a link to an external file.
             * @returns The contents stored in the external file.
             */
            std::vector<std::uint8_t> read_external_reference(const std::string& assetName) const;

        private:
            std::string get_asset_path(const std::string& assetName) const noexcept;

            template <typename T>
            inline T convert(const std::vector<json11::Json>& values) const noexcept;

            template <typename T>
            inline std::shared_ptr<T> get_object(const std::string& name) noexcept;

            template <typename T>
            inline void cache_object(const std::string& name, std::shared_ptr<T> object) noexcept;

        private:
            std::string              _asset_name;
            System::IO::BinaryReader _asset_reader;
            ContentManager*          _content_manager;
            json11::Json             _root;

        private:
            std::map<std::string, std::shared_ptr<SceneR::Graphics::Accessor>>      _accessors       { };
            std::map<std::string, std::shared_ptr<SceneR::Graphics::Buffer>>        _buffers         { };
            std::map<std::string, std::shared_ptr<SceneR::Graphics::BufferView>>    _bufferViews     { };
            std::map<std::string, std::shared_ptr<SceneR::Texture::Surface>>        _images          { };
            std::map<std::string, std::shared_ptr<SceneR::Graphics::ModelMesh>>     _meshes          { };
            std::map<std::string, std::shared_ptr<SceneR::Graphics::Node>>          _nodes           { };
            std::map<std::string, std::shared_ptr<SceneR::Graphics::SamplerState>>  _samplers        { };
            std::map<std::string, std::shared_ptr<SceneR::Graphics::Shader>>        _shaders         { };
            std::map<std::string, std::shared_ptr<SceneR::Graphics::ShaderInclude>> _shader_includes { };
            std::map<std::string, std::shared_ptr<SceneR::Graphics::Texture2D>>     _textures        { };

            template <typename T> friend class ContentTypeReader;
        };
    }
}

namespace SceneR
{
    namespace Content
    {
        template<>
        inline SceneR::Framework::Matrix ContentReader::convert(const std::vector<json11::Json>& values) const noexcept
        {
            SceneR::Framework::Matrix matrix;

            #pragma unroll(16)
            for (int i = 0; i < 16; i++)
            {
                matrix.data[i] = values[i].number_value();
            }

            return matrix;
        }

        template<>
        inline SceneR::Framework::Quaternion ContentReader::convert(const std::vector<json11::Json>& values) const noexcept
        {
            return { values[0].number_value()
                   , values[1].number_value()
                   , values[2].number_value()
                   , values[3].number_value() };
        }

        template<>
        inline SceneR::Framework::Vector2 ContentReader::convert(const std::vector<json11::Json>& values) const noexcept
        {
            return { values[0].number_value()
                   , values[1].number_value() };
        }

        template<>
        inline SceneR::Framework::Vector3 ContentReader::convert(const std::vector<json11::Json>& values) const noexcept
        {
            return { values[0].number_value()
                   , values[1].number_value()
                   , values[2].number_value()};
        }

        template<>
        inline SceneR::Framework::Vector4 ContentReader::convert(const std::vector<json11::Json>& values) const noexcept
        {
            return { values[0].number_value()
                   , values[1].number_value()
                   , values[2].number_value()
                   , values[3].number_value()};
        }

        // Accessors
        template <>
        inline std::shared_ptr<SceneR::Graphics::Accessor> ContentReader::get_object(const std::string& name) noexcept
        {
            return _accessors[name];
        }

        template <>
        inline void ContentReader::cache_object(const std::string&                          name
                                              , std::shared_ptr<SceneR::Graphics::Accessor> object) noexcept
        {
            _accessors[name] = object;
        }

        // Buffers
        template <>
        inline std::shared_ptr<SceneR::Graphics::Buffer> ContentReader::get_object(const std::string& name) noexcept
        {
            return _buffers[name];
        }

        template <>
        inline void ContentReader::cache_object(const std::string&                        name
                                              , std::shared_ptr<SceneR::Graphics::Buffer> object) noexcept
        {
            _buffers[name] = object;
        }

        // Buffer Views
        template <>
        inline std::shared_ptr<SceneR::Graphics::BufferView> ContentReader::get_object(const std::string& name) noexcept
        {
            return _bufferViews[name];
        }

        template <>
        inline void ContentReader::cache_object(const std::string&                            name
                                              , std::shared_ptr<SceneR::Graphics::BufferView> object) noexcept
        {
            _bufferViews[name] = object;
        }

        // Images
        template <>
        inline std::shared_ptr<SceneR::Texture::Surface> ContentReader::get_object(const std::string& name) noexcept
        {
            return _images[name];
        }

        template <>
        inline void ContentReader::cache_object(const std::string&                        name
                                              , std::shared_ptr<SceneR::Texture::Surface> object) noexcept
        {
            _images[name] = object;
        }

        // Meshes
        template <>
        inline std::shared_ptr<SceneR::Graphics::ModelMesh> ContentReader::get_object(const std::string& name) noexcept
        {
            return _meshes[name];
        }

        template <>
        inline void ContentReader::cache_object(const std::string&                           name
                                              , std::shared_ptr<SceneR::Graphics::ModelMesh> object) noexcept
        {
            _meshes[name] = object;
        }

        // Nodes
        template <>
        inline std::shared_ptr<SceneR::Graphics::Node> ContentReader::get_object(const std::string& name) noexcept
        {
            return _nodes[name];
        }

        template <>
        inline void ContentReader::cache_object(const std::string&                      name
                                              , std::shared_ptr<SceneR::Graphics::Node> object) noexcept
        {
            _nodes[name] = object;
        }

        // Samplers
        template <>
        inline std::shared_ptr<SceneR::Graphics::SamplerState> ContentReader::get_object(const std::string& name) noexcept
        {
            return _samplers[name];
        }

        template <>
        inline void ContentReader::cache_object(const std::string&                              name
                                              , std::shared_ptr<SceneR::Graphics::SamplerState> object) noexcept
        {
            _samplers[name] = object;
        }

        // Shaders
        template <>
        inline std::shared_ptr<SceneR::Graphics::Shader> ContentReader::get_object(const std::string& name) noexcept
        {
            return _shaders[name];
        }

        template <>
        inline void ContentReader::cache_object(const std::string&                        name
                                              , std::shared_ptr<SceneR::Graphics::Shader> object) noexcept
        {
            _shaders[name] = object;
        }

        // Shader Includes
        template <>
        inline std::shared_ptr<SceneR::Graphics::ShaderInclude> ContentReader::get_object(const std::string& name) noexcept
        {
            return _shader_includes[name];
        }

        template <>
        inline void ContentReader::cache_object(const std::string&                               name
                                              , std::shared_ptr<SceneR::Graphics::ShaderInclude> object) noexcept
        {
            _shader_includes[name] = object;
        }

        // Textures
        template <>
        inline std::shared_ptr<SceneR::Graphics::Texture2D> ContentReader::get_object(const std::string& name) noexcept
        {
            return _textures[name];
        }

        template <>
        inline void ContentReader::cache_object(const std::string&                           name
                                              , std::shared_ptr<SceneR::Graphics::Texture2D> object) noexcept
        {
            _textures[name] = object;
        }
    }
}

#endif  // CONTENT_CONTENTREADER_HPP
