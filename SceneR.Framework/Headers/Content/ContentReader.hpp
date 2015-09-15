// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef CONTENT_CONTENTREADER_HPP
#define CONTENT_CONTENTREADER_HPP

#include <algorithm>
#include <cstdint>
#include <memory>
#include <vector>
#include <string>

#include <json11.hpp>
#include <Content/ContentTypeReader.hpp>
#include <Framework/Matrix.hpp>
#include <Framework/Quaternion.hpp>
#include <Framework/Vector2.hpp>
#include <Framework/Vector3.hpp>
#include <Framework/Vector4.hpp>
#include <Graphics/Accessor.hpp>
#include <Graphics/Buffer.hpp>
#include <Graphics/BufferView.hpp>
#include <Graphics/Model.hpp>
#include <Graphics/ModelMesh.hpp>
#include <Graphics/Node.hpp>
#include <Graphics/Program.hpp>
#include <Graphics/SamplerState.hpp>
#include <Graphics/Shader.hpp>
#include <Graphics/ShaderInclude.hpp>
#include <Graphics/Texture2D.hpp>
#include <System/IO/BinaryReader.hpp>
#include <System/IO/Stream.hpp>
#include <System/Text/Encoding.hpp>
#include <Texture/Surface.hpp>

namespace SceneR
{
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
            ContentReader(const std::string& assetName, ContentManager* contentManager, System::IO::Stream& stream);

            /**
             * Releases all resources used by the current instance of the ContentReader class.
             */
            ~ContentReader();

        public:
            /**
             * Gets the name of the asset currently being read by this ContentReader.
             */
            const std::string& asset_name() const;

            /**
             * Gets the content manager that owns this ContentReader.
             */
            ContentManager* content_manager() const;

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

                ContentTypeReader<T> reader;
                std::shared_ptr<T>   object = reader.read(this, source);

                cache_object<T>(source.first, object);

                return object;
            }

            /**
             * Reads a link to an external file.
             * @returns The contents stored in the external file.
             */
            std::vector<std::uint8_t> read_external_reference(const std::string& assetName) const;

        private:
            std::string get_asset_path(const std::string& assetName) const;

            template <typename T>
            inline T convert(const std::vector<json11::Json>& values) const;

            template <typename T>
            inline std::shared_ptr<T> get_object(const std::string& name);

            template <typename T>
            inline void cache_object(const std::string& name, std::shared_ptr<T> object);

        private:
            std::string                   _asset_name;
            System::IO::BinaryReader         _asset_reader;
            SceneR::Content::ContentManager* _content_manager;
            json11::Json                     _root;

        private:
            std::map<std::string, std::shared_ptr<SceneR::Graphics::Accessor>>        _accessors;
            std::map<std::string, std::shared_ptr<SceneR::Graphics::Buffer>>          _buffers;
            std::map<std::string, std::shared_ptr<SceneR::Graphics::BufferView>>      _bufferViews;
            std::map<std::string, std::shared_ptr<SceneR::Texture::Surface>>          _images;
            std::map<std::string, std::shared_ptr<SceneR::Graphics::ModelMesh>>       _meshes;
            std::map<std::string, std::shared_ptr<SceneR::Graphics::Node>>            _nodes;
            std::map<std::string, std::shared_ptr<SceneR::Graphics::Program>>         _programs;
            std::map<std::string, std::shared_ptr<SceneR::Graphics::SamplerState>>    _samplers;
            std::map<std::string, std::shared_ptr<SceneR::Graphics::Shader>>          _shaders;
            std::map<std::string, std::shared_ptr<SceneR::Graphics::ShaderInclude>>   _shader_includes;
            std::map<std::string, std::shared_ptr<SceneR::Graphics::EffectTechnique>> _techniques;
            std::map<std::string, std::shared_ptr<SceneR::Graphics::Texture2D>>       _textures;

            template <typename T> friend class ContentTypeReader;
        };
    }
}

template<>
inline SceneR::Framework::Matrix SceneR::Content::ContentReader::convert(const std::vector<json11::Json>& values) const
{
    SceneR::Framework::Matrix matrix;

    #pragma unroll(16)
    for (int i = 0; i < 16; i++)
    {
        matrix.data[i] = values[i].number_value();
    }

    return SceneR::Framework::Matrix::transpose(matrix);
}

template<>
inline SceneR::Framework::Quaternion SceneR::Content::ContentReader::convert(const std::vector<json11::Json>& values) const
{
    return { values[1].number_value()
           , values[2].number_value()
           , values[3].number_value()
           , values[0].number_value(),};
}

template<>
inline SceneR::Framework::Vector2 SceneR::Content::ContentReader::convert(const std::vector<json11::Json>& values) const
{
    return { values[0].number_value()
           , values[1].number_value() };
}

template<>
inline SceneR::Framework::Vector3 SceneR::Content::ContentReader::convert(const std::vector<json11::Json>& values) const
{
    return { values[0].number_value()
           , values[1].number_value()
           , values[2].number_value()};
}

template<>
inline SceneR::Framework::Vector4 SceneR::Content::ContentReader::convert(const std::vector<json11::Json>& values) const
{
    return { values[0].number_value()
           , values[1].number_value()
           , values[2].number_value()
           , values[3].number_value()};
}

// Accessors
template <>
inline std::shared_ptr<SceneR::Graphics::Accessor> SceneR::Content::ContentReader::get_object(const std::string& name)
{
    return _accessors[name];
}

template <>
inline void SceneR::Content::ContentReader::cache_object(const std::string&                          name
                                                       , std::shared_ptr<SceneR::Graphics::Accessor> object)
{
    _accessors[name] = object;
}

// Buffers
template <>
inline std::shared_ptr<SceneR::Graphics::Buffer> SceneR::Content::ContentReader::get_object(const std::string& name)
{
    return _buffers[name];
}

template <>
inline void SceneR::Content::ContentReader::cache_object(const std::string&                        name
                                                       , std::shared_ptr<SceneR::Graphics::Buffer> object)
{
    _buffers[name] = object;
}

// Buffer Views
template <>
inline std::shared_ptr<SceneR::Graphics::BufferView> SceneR::Content::ContentReader::get_object(const std::string& name)
{
    return _bufferViews[name];
}

template <>
inline void SceneR::Content::ContentReader::cache_object(const std::string&                            name
                                                       , std::shared_ptr<SceneR::Graphics::BufferView> object)
{
    _bufferViews[name] = object;
}

// Images
template <>
inline std::shared_ptr<SceneR::Texture::Surface> SceneR::Content::ContentReader::get_object(const std::string& name)
{
    return _images[name];
}

template <>
inline void SceneR::Content::ContentReader::cache_object(const std::string&                        name
                                                       , std::shared_ptr<SceneR::Texture::Surface> object)
{
    _images[name] = object;
}

// Meshes
template <>
inline std::shared_ptr<SceneR::Graphics::ModelMesh> SceneR::Content::ContentReader::get_object(const std::string& name)
{
    return _meshes[name];
}

template <>
inline void SceneR::Content::ContentReader::cache_object(const std::string&                           name
                                                       , std::shared_ptr<SceneR::Graphics::ModelMesh> object)
{
    _meshes[name] = object;
}

// Nodes
template <>
inline std::shared_ptr<SceneR::Graphics::Node> SceneR::Content::ContentReader::get_object(const std::string& name)
{
    return _nodes[name];
}

template <>
inline void SceneR::Content::ContentReader::cache_object(const std::string&                      name
                                                       , std::shared_ptr<SceneR::Graphics::Node> object)
{
    _nodes[name] = object;
}

// Programs
template <>
inline std::shared_ptr<SceneR::Graphics::Program> SceneR::Content::ContentReader::get_object(const std::string& name)
{
    return _programs[name];
}

template <>
inline void SceneR::Content::ContentReader::cache_object(const std::string&                         name
                                                       , std::shared_ptr<SceneR::Graphics::Program> object)
{
    _programs[name] = object;
}

// Samplers
template <>
inline std::shared_ptr<SceneR::Graphics::SamplerState> SceneR::Content::ContentReader::get_object(const std::string& name)
{
    return _samplers[name];
}

template <>
inline void SceneR::Content::ContentReader::cache_object(const std::string&                              name
                                                       , std::shared_ptr<SceneR::Graphics::SamplerState> object)
{
    _samplers[name] = object;
}

// Shaders
template <>
inline std::shared_ptr<SceneR::Graphics::Shader> SceneR::Content::ContentReader::get_object(const std::string& name)
{
    return _shaders[name];
}

template <>
inline void SceneR::Content::ContentReader::cache_object(const std::string&                        name
                                                       , std::shared_ptr<SceneR::Graphics::Shader> object)
{
    _shaders[name] = object;
}

// Shader Includes
template <>
inline std::shared_ptr<SceneR::Graphics::ShaderInclude> SceneR::Content::ContentReader::get_object(const std::string& name)
{
    return _shader_includes[name];
}

template <>
inline void SceneR::Content::ContentReader::cache_object(const std::string&                               name
                                                       , std::shared_ptr<SceneR::Graphics::ShaderInclude> object)
{
    _shader_includes[name] = object;
}

// Techniques
template <>
inline std::shared_ptr<SceneR::Graphics::EffectTechnique> SceneR::Content::ContentReader::get_object(const std::string& name)
{
    return _techniques[name];
}

template <>
inline void SceneR::Content::ContentReader::cache_object(const std::string&                                 name
                                                       , std::shared_ptr<SceneR::Graphics::EffectTechnique> object)
{
    _techniques[name] = object;
}

// Textures
template <>
inline std::shared_ptr<SceneR::Graphics::Texture2D> SceneR::Content::ContentReader::get_object(const std::string& name)
{
    return _textures[name];
}

template <>
inline void SceneR::Content::ContentReader::cache_object(const std::string&                           name
                                                       , std::shared_ptr<SceneR::Graphics::Texture2D> object)
{
    _textures[name] = object;
}

#endif  // CONTENT_CONTENTREADER_HPP
