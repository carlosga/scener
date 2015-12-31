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
#include "SceneR/Graphics/ModelBone.hpp"
#include "SceneR/IO/BinaryReader.hpp"
#include "SceneR/IO/Stream.hpp"
#include "SceneR/Math/Matrix.hpp"
#include "SceneR/Math/Quaternion.hpp"
#include "SceneR/Math/Vector2.hpp"
#include "SceneR/Math/Vector3.hpp"
#include "SceneR/Math/Vector4.hpp"

namespace SceneR { namespace Content { namespace DDS {

class Surface;

}}}

namespace SceneR { namespace Content { namespace GLTF {

class Accessor;
class Buffer;
class BufferView;

}}}

namespace SceneR { namespace Graphics {

class EffectTechnique;
class Model;
class ModelMesh;
class Program;
class SamplerState;
class Shader;
class ShaderInclude;
class Texture2D;

}}

namespace SceneR { namespace Content {

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
    ContentReader(const std::string& assetName
                , ContentManager*    contentManager
                , IO::Stream&        stream);

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
    std::shared_ptr<Graphics::Model> read_asset();

private:
    bool read_header();

    std::string get_asset_path(const std::string& assetName) const noexcept;

    std::vector<std::uint8_t> read_external_reference(const std::string& assetName) const;

    std::shared_ptr<GLTF::Node> find_joint_node(const std::string& jointName) const;

private:
    template<typename T>
    inline std::shared_ptr<T> read_object(const std::string& key);

    template<typename T>
    inline std::shared_ptr<T> read_object(const std::string& key, const json11::Json& source);

    template<typename T>
    inline std::shared_ptr<T> read_object_instance(const std::string& key);

    template<typename T>
    inline std::shared_ptr<T> read_object_instance(const std::string& key, const json11::Json& source);

    template <typename T>
    inline std::shared_ptr<T> get_object(const std::string& key) noexcept;

    template <typename T>
    inline void cache_object(const std::string& key, std::shared_ptr<T> object) noexcept;

    template <typename T>
    inline T convert(const std::vector<json11::Json>& values) const noexcept;

private:
    std::string              _asset_name;
    SceneR::IO::BinaryReader _asset_reader;
    ContentManager*          _content_manager;
    json11::Json             _root;

private:
    std::map<std::string, std::shared_ptr<SceneR::Content::GLTF::Accessor>>   _accessors       { };
    std::map<std::string, std::shared_ptr<SceneR::Content::GLTF::Buffer>>     _buffers         { };
    std::map<std::string, std::shared_ptr<SceneR::Content::GLTF::BufferView>> _bufferViews     { };
    std::map<std::string, std::shared_ptr<SceneR::Content::GLTF::Node>>       _nodes           { };
    std::map<std::string, std::shared_ptr<SceneR::Content::DDS::Surface>>     _images          { };
    std::map<std::string, std::shared_ptr<SceneR::Graphics::ModelMesh>>       _meshes          { };
    std::map<std::string, std::shared_ptr<SceneR::Graphics::SamplerState>>    _samplers        { };
    std::map<std::string, std::shared_ptr<SceneR::Graphics::Shader>>          _shaders         { };
    std::map<std::string, std::shared_ptr<SceneR::Graphics::ShaderInclude>>   _shader_includes { };
    std::map<std::string, std::shared_ptr<SceneR::Graphics::Texture2D>>       _textures        { };

    template <typename T> friend class SceneR::Content::Readers::ContentTypeReader;
};

//
// IMPLEMENTATION

// Accessors
template<>
inline std::shared_ptr<GLTF::Accessor> ContentReader::read_object(const std::string& key)
{
    return read_object<GLTF::Accessor>(key, _root["accessors"][key]);
}

template <>
inline std::shared_ptr<GLTF::Accessor> ContentReader::get_object(const std::string& key) noexcept
{
    return _accessors[key];
}

template <>
inline void ContentReader::cache_object(const std::string&              key
                                      , std::shared_ptr<GLTF::Accessor> object) noexcept
{
    _accessors[key] = object;
}

// Buffers
template<>
inline std::shared_ptr<GLTF::Buffer> ContentReader::read_object(const std::string& key)
{
    return read_object<GLTF::Buffer>(key, _root["buffers"][key]);
}

template <>
inline std::shared_ptr<GLTF::Buffer> ContentReader::get_object(const std::string& key) noexcept
{
    return _buffers[key];
}

template <>
inline void ContentReader::cache_object(const std::string&            key
                                      , std::shared_ptr<GLTF::Buffer> object) noexcept
{
    _buffers[key] = object;
}

// Buffer Views
template<>
inline std::shared_ptr<GLTF::BufferView> ContentReader::read_object(const std::string& key)
{
    return read_object<GLTF::BufferView>(key, _root["bufferViews"][key]);
}

template <>
inline std::shared_ptr<GLTF::BufferView> ContentReader::get_object(const std::string& key) noexcept
{
    return _bufferViews[key];
}

template <>
inline void ContentReader::cache_object(const std::string&                key
                                      , std::shared_ptr<GLTF::BufferView> object) noexcept
{
    _bufferViews[key] = object;
}

// Effect techniques
template<>
inline std::shared_ptr<Graphics::EffectTechnique> ContentReader::read_object_instance(const std::string& key)
{
    return read_object_instance<Graphics::EffectTechnique>(key, _root["techniques"][key]);
}

// Images
template<>
inline std::shared_ptr<DDS::Surface> ContentReader::read_object(const std::string& key)
{
    return read_object<DDS::Surface>(key, _root["images"][key]);
}

template <>
inline std::shared_ptr<DDS::Surface> ContentReader::get_object(const std::string& key) noexcept
{
    return _images[key];
}

template <>
inline void ContentReader::cache_object(const std::string&            key
                                      , std::shared_ptr<DDS::Surface> object) noexcept
{
    _images[key] = object;
}

// Meshes
template<>
inline std::shared_ptr<Graphics::ModelMesh> ContentReader::read_object(const std::string& key)
{
    return read_object<Graphics::ModelMesh>(key, _root["meshes"][key]);
}

template <>
inline std::shared_ptr<Graphics::ModelMesh> ContentReader::get_object(const std::string& key) noexcept
{
    return _meshes[key];
}

template <>
inline void ContentReader::cache_object(const std::string&                   key
                                      , std::shared_ptr<Graphics::ModelMesh> object) noexcept
{
    _meshes[key] = object;
}

// Nodes
template<>
inline std::shared_ptr<GLTF::Node> ContentReader::read_object(const std::string& key)
{
    return read_object<GLTF::Node>(key, _root["nodes"][key]);
}

template <>
inline std::shared_ptr<GLTF::Node> ContentReader::get_object(const std::string& key) noexcept
{
    return _nodes[key];
}

template <>
inline void ContentReader::cache_object(const std::string&          key
                                      , std::shared_ptr<GLTF::Node> object) noexcept
{
    _nodes[key] = object;
}

// Programs
template<>
inline std::shared_ptr<Graphics::Program> ContentReader::read_object_instance(const std::string& key)
{
    return read_object_instance<Graphics::Program>(key, _root["programs"][key]);
}

// Samplers
template<>
inline std::shared_ptr<Graphics::SamplerState> ContentReader::read_object(const std::string& key)
{
    return read_object<Graphics::SamplerState>(key, _root["samplers"][key]);
}

template <>
inline std::shared_ptr<SceneR::Graphics::SamplerState> ContentReader::get_object(const std::string& key) noexcept
{
    return _samplers[key];
}

template <>
inline void ContentReader::cache_object(const std::string&                      key
                                      , std::shared_ptr<Graphics::SamplerState> object) noexcept
{
    _samplers[key] = object;
}

// Shaders
template<>
inline std::shared_ptr<Graphics::Shader> ContentReader::read_object(const std::string& key)
{
    return read_object<Graphics::Shader>(key, _root["shaders"][key]);
}

template <>
inline std::shared_ptr<Graphics::Shader> ContentReader::get_object(const std::string& key) noexcept
{
    return _shaders[key];
}

template <>
inline void ContentReader::cache_object(const std::string&                key
                                      , std::shared_ptr<Graphics::Shader> object) noexcept
{
    _shaders[key] = object;
}

// Shader Includes
template <>
inline std::shared_ptr<Graphics::ShaderInclude> ContentReader::get_object(const std::string& key) noexcept
{
    return _shader_includes[key];
}

template <>
inline void ContentReader::cache_object(const std::string&                       key
                                      , std::shared_ptr<Graphics::ShaderInclude> object) noexcept
{
    _shader_includes[key] = object;
}

// Textures
template<>
inline std::shared_ptr<Graphics::Texture2D> ContentReader::read_object(const std::string& key)
{
    return read_object<Graphics::Texture2D>(key, _root["textures"][key]);
}

template <>
inline std::shared_ptr<Graphics::Texture2D> ContentReader::get_object(const std::string& key) noexcept
{
    return _textures[key];
}

template <>
inline void ContentReader::cache_object(const std::string&                   key
                                      , std::shared_ptr<Graphics::Texture2D> object) noexcept
{
    _textures[key] = object;
}

// Common read object operations
template<typename T>
inline std::shared_ptr<T> ContentReader::read_object(const std::string& key, const json11::Json& source)
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
inline std::shared_ptr<T> ContentReader::read_object_instance(const std::string& key, const json11::Json& source)
{
    Readers::ContentTypeReader<T> reader;

    return reader.read(this, key, source);
}

template<>
inline Math::Matrix ContentReader::convert(const std::vector<json11::Json>& values) const noexcept
{
    Math::Matrix matrix;

    #pragma unroll(16)
    for (int i = 0; i < 16; i++)
    {
        matrix.data[i] = values[i].number_value();
    }

    return matrix;
}

// Type conversion operations
template<>
inline Math::Quaternion ContentReader::convert(const std::vector<json11::Json>& values) const noexcept
{
    return { values[0].number_value()
           , values[1].number_value()
           , values[2].number_value()
           , values[3].number_value() };
}

template<>
inline Math::Vector2 ContentReader::convert(const std::vector<json11::Json>& values) const noexcept
{
    return { values[0].number_value()
           , values[1].number_value() };
}

template<>
inline Math::Vector3 ContentReader::convert(const std::vector<json11::Json>& values) const noexcept
{
    return { values[0].number_value()
           , values[1].number_value()
           , values[2].number_value()};
}

template<>
inline Math::Vector4 ContentReader::convert(const std::vector<json11::Json>& values) const noexcept
{
    return { values[0].number_value()
           , values[1].number_value()
           , values[2].number_value()
           , values[3].number_value()};
}

}}

#endif // SCENER_CONTENT_CONTENTREADER_HPP
