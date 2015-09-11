// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef CONTENT_CONTENTREADER_HPP
#define CONTENT_CONTENTREADER_HPP

#include <algorithm>
#include <cstdint>
#include <memory>
#include <vector>
#include <string>

#include <Content/json11.hpp>
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
#include <System/IO/BinaryReader.hpp>
#include <System/IO/Stream.hpp>
#include <System/Text/Encoding.hpp>

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
            ContentReader(const std::u16string&            assetName
                        , SceneR::Content::ContentManager* contentManager
                        , System::IO::Stream&              stream);

            /**
             * Releases all resources used by the current instance of the ContentReader class.
             */
            ~ContentReader();

        public:
            /**
             * Gets the name of the asset currently being read by this ContentReader.
             */
            const std::u16string& asset_name() const;

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
                ContentTypeReader<T> reader;
                return reader.read(this, source);
            }

            /**
             * Reads a link to an external file.
             * @returns The contents stored in the external file.
             */
            std::vector<std::uint8_t> read_external_reference(const std::string& assetName) const;

            /**
             * Reads a link to an external file.
             * @returns The contents stored in the external file.
             */
            std::vector<std::uint8_t> read_external_reference(const std::u16string& assetName) const;

            template <typename T>
            inline T convert(const std::vector<json11::Json>& values) const;

            template <typename T>
            inline std::shared_ptr<T> find_object(const std::string& name) const;

        private:
            std::u16string                   _asset_name;
            System::IO::BinaryReader         _asset_reader;
            SceneR::Content::ContentManager* _content_manager;
            json11::Json                     _root;

            std::vector<std::shared_ptr<SceneR::Graphics::Accessor>>   _accessors;
            std::vector<std::shared_ptr<SceneR::Graphics::Buffer>>     _buffers;
            std::vector<std::shared_ptr<SceneR::Graphics::BufferView>> _buffer_views;
            std::vector<std::shared_ptr<SceneR::Graphics::ModelMesh>>  _meshes;
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

template <>
inline std::shared_ptr<SceneR::Graphics::Accessor> SceneR::Content::ContentReader::find_object(const std::string& name) const
{
    auto oname = System::Text::Encoding::convert(name);
    auto it = find_if(_accessors.begin()
                    , _accessors.end()
                    , [&](std::shared_ptr<SceneR::Graphics::Accessor> accessor) -> bool
        {
            return (accessor->name() == oname);
        });

    return ((it != _accessors.end()) ? *it : nullptr);
}

template <>
inline std::shared_ptr<SceneR::Graphics::Buffer> SceneR::Content::ContentReader::find_object(const std::string& name) const
{
    auto oname = System::Text::Encoding::convert(name);
    auto it = find_if(_buffers.begin()
                    , _buffers.end()
                    , [&](std::shared_ptr<SceneR::Graphics::Buffer> buffer) -> bool
        {
            return (buffer->name() == oname);
        });

    return ((it != _buffers.end()) ? *it : nullptr);
}

template <>
inline std::shared_ptr<SceneR::Graphics::BufferView> SceneR::Content::ContentReader::find_object(const std::string& name) const
{
    auto oname = System::Text::Encoding::convert(name);
    auto it = find_if(_buffer_views.begin()
                    , _buffer_views.end()
                    , [&](std::shared_ptr<SceneR::Graphics::BufferView> bufferView) -> bool
        {
            return (bufferView->name() == oname);
        });

    return ((it != _buffer_views.end()) ? *it : nullptr);
}

template <>
inline std::shared_ptr<SceneR::Graphics::ModelMesh> SceneR::Content::ContentReader::find_object(const std::string& name) const
{
    auto oname = System::Text::Encoding::convert(name);
    auto it = find_if(_meshes.begin()
                    , _meshes.end()
                    , [&](std::shared_ptr<SceneR::Graphics::ModelMesh> mesh) -> bool
        {
            return (mesh->name() == oname);
        });

    return ((it != _meshes.end()) ? *it : nullptr);
}

#endif  // CONTENT_CONTENTREADER_HPP
