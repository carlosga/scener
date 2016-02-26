// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_CONTENT_CONTENTREADER_HPP
#define SCENER_CONTENT_CONTENTREADER_HPP

#include <cstdint>
#include <map>
#include <memory>
#include <vector>
#include <string>

#include <json11.hpp>

#include "SceneR/Content/Readers/ContentTypeReader.hpp"
#include "SceneR/Content/GLTF/Node.hpp"
#include "SceneR/Graphics/Bone.hpp"
#include "SceneR/IO/BinaryReader.hpp"
#include "SceneR/IO/Stream.hpp"
#include "scener/math/matrix.hpp"
#include "scener/math/quaternion.hpp"
#include "scener/math/vector.hpp"

namespace scener { namespace content { namespace dds { class Surface; } } }

namespace scener { namespace content { namespace gltf {

class Accessor;
class Buffer;
class BufferView;

}}}

namespace scener { namespace graphics {

class  EffectTechnique;
class  Model;
class  ModelMesh;
class  SamplerState;
class  Texture2D;

namespace opengl {

class Program;
class Shader;

}

}}

namespace scener { namespace content {

class ContentManager;

/// Reads application content_manager from disk.
class ContentReader final
{
public:
    /// Initializes a new instance of the ContentReader.
    /// \param assetName the name of the asset to be readed.
    /// \param contentManager the content_manager that owns this ContentReader.
    /// \param stream the base stream.
    ContentReader(const std::string& assetName, ContentManager* contentManager, io::Stream& stream) noexcept;

    /// Releases all resources used by the current instance of the ContentReader class.
    ~ContentReader() = default;

public:
    /// Gets the name of the asset currently being read by this ContentReader.
    const std::string& asset_name() const noexcept;

    /// Gets the content manager that owns this ContentReader.
    ContentManager* content_manager() const noexcept;

 public:
    /// Reads the contexts of the current asset.
    /// \returns The contexts of the current asset.
    std::shared_ptr<graphics::Model> read_asset() noexcept;

private:
    bool read_header() noexcept;

    std::string get_asset_path(const std::string& assetName) const noexcept;

    std::vector<std::uint8_t> read_external_reference(const std::string& assetName) const noexcept;

    std::shared_ptr<gltf::Node> find_joint_node(const std::string& jointName) const noexcept;

private:
    template<typename T>
    inline std::shared_ptr<T> read_object(const std::string& key) noexcept;

    template<typename T>
    inline std::shared_ptr<T> read_object(const std::string& key, const json11::Json& source) noexcept;

    template<typename T>
    inline std::shared_ptr<T> read_object_instance(const std::string& key) noexcept;

    template<typename T>
    inline std::shared_ptr<T> read_object_instance(const std::string& key, const json11::Json& source) noexcept;

    template <typename T>
    inline std::shared_ptr<T> get_object(const std::string& key) noexcept;

    template <typename T>
    inline void cache_object(const std::string& key, std::shared_ptr<T> object) noexcept;

    template <typename T>
    inline T convert(const std::vector<json11::Json>& values) const noexcept;

private:
    std::string              _asset_name;
    scener::io::BinaryReader _asset_reader;
    ContentManager*          _content_manager;
    json11::Json             _root;

private:
    std::map<std::string, std::shared_ptr<scener::content::gltf::Accessor>>   _accessors   { };
    std::map<std::string, std::shared_ptr<scener::content::gltf::Buffer>>     _buffers     { };
    std::map<std::string, std::shared_ptr<scener::content::gltf::BufferView>> _bufferViews { };
    std::map<std::string, std::shared_ptr<scener::content::gltf::Node>>       _nodes       { };
    std::map<std::string, std::shared_ptr<scener::content::dds::Surface>>     _images      { };
    std::map<std::string, std::shared_ptr<scener::graphics::ModelMesh>>       _meshes      { };
    std::map<std::string, std::shared_ptr<scener::graphics::SamplerState>>    _samplers    { };
    std::map<std::string, std::shared_ptr<scener::graphics::opengl::Shader>>  _shaders     { };
    std::map<std::string, std::shared_ptr<scener::graphics::Texture2D>>       _textures    { };

    template <typename T> friend class scener::content::readers::ContentTypeReader;
};

//
// IMPLEMENTATION

// Accessors
template<>
inline std::shared_ptr<gltf::Accessor> ContentReader::read_object(const std::string& key) noexcept
{
    return read_object<gltf::Accessor>(key, _root["accessors"][key]);
}

template <>
inline std::shared_ptr<gltf::Accessor> ContentReader::get_object(const std::string& key) noexcept
{
    return _accessors[key];
}

template <>
inline void ContentReader::cache_object(const std::string&              key
                                      , std::shared_ptr<gltf::Accessor> object) noexcept
{
    _accessors[key] = object;
}

// Buffers
template<>
inline std::shared_ptr<gltf::Buffer> ContentReader::read_object(const std::string& key) noexcept
{
    return read_object<gltf::Buffer>(key, _root["buffers"][key]);
}

template <>
inline std::shared_ptr<gltf::Buffer> ContentReader::get_object(const std::string& key) noexcept
{
    return _buffers[key];
}

template <>
inline void ContentReader::cache_object(const std::string&            key
                                      , std::shared_ptr<gltf::Buffer> object) noexcept
{
    _buffers[key] = object;
}

// Buffer Views
template<>
inline std::shared_ptr<gltf::BufferView> ContentReader::read_object(const std::string& key) noexcept
{
    return read_object<gltf::BufferView>(key, _root["bufferViews"][key]);
}

template <>
inline std::shared_ptr<gltf::BufferView> ContentReader::get_object(const std::string& key) noexcept
{
    return _bufferViews[key];
}

template <>
inline void ContentReader::cache_object(const std::string&                key
                                      , std::shared_ptr<gltf::BufferView> object) noexcept
{
    _bufferViews[key] = object;
}

// Effect techniques
template<>
inline std::shared_ptr<graphics::EffectTechnique> ContentReader::read_object_instance(const std::string& key) noexcept
{
    return read_object_instance<graphics::EffectTechnique>(key, _root["techniques"][key]);
}

// Images
template<>
inline std::shared_ptr<dds::Surface> ContentReader::read_object(const std::string& key) noexcept
{
    return read_object<dds::Surface>(key, _root["images"][key]);
}

template <>
inline std::shared_ptr<dds::Surface> ContentReader::get_object(const std::string& key) noexcept
{
    return _images[key];
}

template <>
inline void ContentReader::cache_object(const std::string&            key
                                      , std::shared_ptr<dds::Surface> object) noexcept
{
    _images[key] = object;
}

// Meshes
template<>
inline std::shared_ptr<graphics::ModelMesh> ContentReader::read_object(const std::string& key) noexcept
{
    return read_object<graphics::ModelMesh>(key, _root["meshes"][key]);
}

template <>
inline std::shared_ptr<graphics::ModelMesh> ContentReader::get_object(const std::string& key) noexcept
{
    return _meshes[key];
}

template <>
inline void ContentReader::cache_object(const std::string&                   key
                                      , std::shared_ptr<graphics::ModelMesh> object) noexcept
{
    _meshes[key] = object;
}

// Nodes
template<>
inline std::shared_ptr<gltf::Node> ContentReader::read_object(const std::string& key) noexcept
{
    return read_object<gltf::Node>(key, _root["nodes"][key]);
}

template <>
inline std::shared_ptr<gltf::Node> ContentReader::get_object(const std::string& key) noexcept
{
    return _nodes[key];
}

template <>
inline void ContentReader::cache_object(const std::string&          key
                                      , std::shared_ptr<gltf::Node> object) noexcept
{
    _nodes[key] = object;
}

// Programs
template<>
inline std::shared_ptr<graphics::opengl::Program> ContentReader::read_object_instance(const std::string& key) noexcept
{
    return read_object_instance<graphics::opengl::Program>(key, _root["programs"][key]);
}

// Samplers
template<>
inline std::shared_ptr<graphics::SamplerState> ContentReader::read_object(const std::string& key) noexcept
{
    return read_object<graphics::SamplerState>(key, _root["samplers"][key]);
}

template <>
inline std::shared_ptr<scener::graphics::SamplerState> ContentReader::get_object(const std::string& key) noexcept
{
    return _samplers[key];
}

template <>
inline void ContentReader::cache_object(const std::string&                      key
                                      , std::shared_ptr<graphics::SamplerState> object) noexcept
{
    _samplers[key] = object;
}

// Shaders
template<>
inline std::shared_ptr<graphics::opengl::Shader> ContentReader::read_object(const std::string& key) noexcept
{
    return read_object<graphics::opengl::Shader>(key, _root["shaders"][key]);
}

template <>
inline std::shared_ptr<graphics::opengl::Shader> ContentReader::get_object(const std::string& key) noexcept
{
    return _shaders[key];
}

template <>
inline void ContentReader::cache_object(const std::string&                        key
                                      , std::shared_ptr<graphics::opengl::Shader> object) noexcept
{
    _shaders[key] = object;
}

// Textures
template<>
inline std::shared_ptr<graphics::Texture2D> ContentReader::read_object(const std::string& key) noexcept
{
    return read_object<graphics::Texture2D>(key, _root["textures"][key]);
}

template <>
inline std::shared_ptr<graphics::Texture2D> ContentReader::get_object(const std::string& key) noexcept
{
    return _textures[key];
}

template <>
inline void ContentReader::cache_object(const std::string&                   key
                                      , std::shared_ptr<graphics::Texture2D> object) noexcept
{
    _textures[key] = object;
}

// Common read object operations
template<typename T>
inline std::shared_ptr<T> ContentReader::read_object(const std::string& key, const json11::Json& source) noexcept
{
    auto instance = get_object<T>(key);
    if (instance != nullptr)
    {
        return instance;
    }

    auto object = read_object_instance<T>(key, source);

    cache_object<T>(key, object);

    return object;
}

template<typename T>
inline std::shared_ptr<T> ContentReader::read_object_instance(const std::string& key, const json11::Json& source) noexcept
{
    readers::ContentTypeReader<T> reader;

    return reader.read(this, key, source);
}

template<>
inline math::matrix4 ContentReader::convert(const std::vector<json11::Json>& values) const noexcept
{
    math::matrix4 matrix;

    for (std::size_t i = 0; i < 4; ++i)
    {
        for (std::size_t j = 0; j < 4; ++j)
        {
            matrix[i][j] = static_cast<float>(values[i * 4 + j].number_value());
        }
    }

    return matrix;
}

// Type conversion operations
template<>
inline math::quaternion ContentReader::convert(const std::vector<json11::Json>& values) const noexcept
{
    return { static_cast<float>(values[0].number_value())
           , static_cast<float>(values[1].number_value())
           , static_cast<float>(values[2].number_value())
           , static_cast<float>(values[3].number_value()) };
}

template<>
inline math::vector2 ContentReader::convert(const std::vector<json11::Json>& values) const noexcept
{
    return { static_cast<float>(values[0].number_value())
           , static_cast<float>(values[1].number_value()) };
}

template<>
inline math::vector3 ContentReader::convert(const std::vector<json11::Json>& values) const noexcept
{
    return { static_cast<float>(values[0].number_value())
           , static_cast<float>(values[1].number_value())
           , static_cast<float>(values[2].number_value()) };
}

template<>
inline math::vector4 ContentReader::convert(const std::vector<json11::Json>& values) const noexcept
{
    return { static_cast<float>(values[0].number_value())
           , static_cast<float>(values[1].number_value())
           , static_cast<float>(values[2].number_value())
           , static_cast<float>(values[3].number_value()) };
}

}}

#endif // SCENER_CONTENT_CONTENTREADER_HPP
