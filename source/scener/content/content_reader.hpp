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

#include "scener/content/readers/content_type_reader.hpp"
#include "scener/content/gltf/node.hpp"
#include "scener/graphics/bone.hpp"
#include "scener/io/binary_reader.hpp"
#include "scener/io/stream.hpp"
#include "scener/math/matrix.hpp"
#include "scener/math/quaternion.hpp"
#include "scener/math/vector.hpp"

namespace scener { namespace content { namespace dds { class surface; } } }

namespace scener { namespace content { namespace gltf {

class accessor;
class buffer;
class buffer_view;

}}}

namespace scener { namespace graphics {

class effect_technique;
class model;
class model_mesh;
class sampler_state;
class texture2d;

namespace opengl {

class program;
class shader;

}

}}

namespace scener { namespace content {

class content_manager;

/// Reads application content_manager from disk.
class content_reader final
{
public:
    /// Initializes a new instance of the ContentReader.
    /// \param assetname the name of the asset to be readed.
    /// \param manager the content_manager that owns this ContentReader.
    /// \param stream the base stream.
    content_reader(const std::string& assetname, content::content_manager* manager, io::stream& stream) noexcept;

    /// Releases all resources used by the current instance of the ContentReader class.
    ~content_reader() = default;

public:
    /// Gets the name of the asset currently being read by this ContentReader.
    const std::string& asset_name() const noexcept;

    /// Gets the content manager that owns this ContentReader.
    content::content_manager* content_manager() const noexcept;

 public:
    /// Reads the contexts of the current asset.
    /// \returns The contexts of the current asset.
    std::shared_ptr<graphics::model> read_asset() noexcept;

private:
    bool read_header() noexcept;

    std::string get_asset_path(const std::string& assetname) const noexcept;

    std::vector<std::uint8_t> read_external_reference(const std::string& assetname) const noexcept;

    std::shared_ptr<gltf::node> find_joint_node(const std::string& jointname) const noexcept;

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
    std::string               _asset_name;
    io::binary_reader         _asset_reader;
    content::content_manager* _content_manager;
    json11::Json              _root;

private:
    std::map<std::string, std::shared_ptr<scener::content::gltf::accessor>>    _accessors   { };
    std::map<std::string, std::shared_ptr<scener::content::gltf::buffer>>      _buffers     { };
    std::map<std::string, std::shared_ptr<scener::content::gltf::buffer_view>> _bufferViews { };
    std::map<std::string, std::shared_ptr<scener::content::gltf::node>>        _nodes       { };
    std::map<std::string, std::shared_ptr<scener::content::dds::surface>>      _images      { };
    std::map<std::string, std::shared_ptr<scener::graphics::model_mesh>>       _meshes      { };
    std::map<std::string, std::shared_ptr<scener::graphics::sampler_state>>    _samplers    { };
    std::map<std::string, std::shared_ptr<scener::graphics::opengl::shader>>   _shaders     { };
    std::map<std::string, std::shared_ptr<scener::graphics::texture2d>>        _textures    { };

    template <typename T> friend class scener::content::readers::content_type_reader;
};

//
// IMPLEMENTATION

// Accessors
template<>
inline std::shared_ptr<gltf::accessor> content_reader::read_object(const std::string& key) noexcept
{
    return read_object<gltf::accessor>(key, _root["accessors"][key]);
}

template <>
inline std::shared_ptr<gltf::accessor> content_reader::get_object(const std::string& key) noexcept
{
    return _accessors[key];
}

template <>
inline void content_reader::cache_object(const std::string&              key
                                       , std::shared_ptr<gltf::accessor> object) noexcept
{
    _accessors[key] = object;
}

// Buffers
template<>
inline std::shared_ptr<gltf::buffer> content_reader::read_object(const std::string& key) noexcept
{
    return read_object<gltf::buffer>(key, _root["buffers"][key]);
}

template <>
inline std::shared_ptr<gltf::buffer> content_reader::get_object(const std::string& key) noexcept
{
    return _buffers[key];
}

template <>
inline void content_reader::cache_object(const std::string&            key
                                       , std::shared_ptr<gltf::buffer> object) noexcept
{
    _buffers[key] = object;
}

// Buffer Views
template<>
inline std::shared_ptr<gltf::buffer_view> content_reader::read_object(const std::string& key) noexcept
{
    return read_object<gltf::buffer_view>(key, _root["bufferViews"][key]);
}

template <>
inline std::shared_ptr<gltf::buffer_view> content_reader::get_object(const std::string& key) noexcept
{
    return _bufferViews[key];
}

template <>
inline void content_reader::cache_object(const std::string&                key
                                      , std::shared_ptr<gltf::buffer_view> object) noexcept
{
    _bufferViews[key] = object;
}

// Effect techniques
template<>
inline std::shared_ptr<graphics::effect_technique> content_reader::read_object_instance(const std::string& key) noexcept
{
    return read_object_instance<graphics::effect_technique>(key, _root["techniques"][key]);
}

// Images
template<>
inline std::shared_ptr<dds::surface> content_reader::read_object(const std::string& key) noexcept
{
    return read_object<dds::surface>(key, _root["images"][key]);
}

template <>
inline std::shared_ptr<dds::surface> content_reader::get_object(const std::string& key) noexcept
{
    return _images[key];
}

template <>
inline void content_reader::cache_object(const std::string&            key
                                       , std::shared_ptr<dds::surface> object) noexcept
{
    _images[key] = object;
}

// Meshes
template<>
inline std::shared_ptr<graphics::model_mesh> content_reader::read_object(const std::string& key) noexcept
{
    return read_object<graphics::model_mesh>(key, _root["meshes"][key]);
}

template <>
inline std::shared_ptr<graphics::model_mesh> content_reader::get_object(const std::string& key) noexcept
{
    return _meshes[key];
}

template <>
inline void content_reader::cache_object(const std::string&                   key
                                       , std::shared_ptr<graphics::model_mesh> object) noexcept
{
    _meshes[key] = object;
}

// Nodes
template<>
inline std::shared_ptr<gltf::node> content_reader::read_object(const std::string& key) noexcept
{
    return read_object<gltf::node>(key, _root["nodes"][key]);
}

template <>
inline std::shared_ptr<gltf::node> content_reader::get_object(const std::string& key) noexcept
{
    return _nodes[key];
}

template <>
inline void content_reader::cache_object(const std::string&          key
                                       , std::shared_ptr<gltf::node> object) noexcept
{
    _nodes[key] = object;
}

// Programs
template<>
inline std::shared_ptr<graphics::opengl::program> content_reader::read_object_instance(const std::string& key) noexcept
{
    return read_object_instance<graphics::opengl::program>(key, _root["programs"][key]);
}

// Samplers
template<>
inline std::shared_ptr<graphics::sampler_state> content_reader::read_object(const std::string& key) noexcept
{
    return read_object<graphics::sampler_state>(key, _root["samplers"][key]);
}

template <>
inline std::shared_ptr<scener::graphics::sampler_state> content_reader::get_object(const std::string& key) noexcept
{
    return _samplers[key];
}

template <>
inline void content_reader::cache_object(const std::string&                      key
                                       , std::shared_ptr<graphics::sampler_state> object) noexcept
{
    _samplers[key] = object;
}

// Shaders
template<>
inline std::shared_ptr<graphics::opengl::shader> content_reader::read_object(const std::string& key) noexcept
{
    return read_object<graphics::opengl::shader>(key, _root["shaders"][key]);
}

template <>
inline std::shared_ptr<graphics::opengl::shader> content_reader::get_object(const std::string& key) noexcept
{
    return _shaders[key];
}

template <>
inline void content_reader::cache_object(const std::string&                        key
                                       , std::shared_ptr<graphics::opengl::shader> object) noexcept
{
    _shaders[key] = object;
}

// Textures
template<>
inline std::shared_ptr<graphics::texture2d> content_reader::read_object(const std::string& key) noexcept
{
    return read_object<graphics::texture2d>(key, _root["textures"][key]);
}

template <>
inline std::shared_ptr<graphics::texture2d> content_reader::get_object(const std::string& key) noexcept
{
    return _textures[key];
}

template <>
inline void content_reader::cache_object(const std::string&                   key
                                       , std::shared_ptr<graphics::texture2d> object) noexcept
{
    _textures[key] = object;
}

// Common read object operations
template<typename T>
inline std::shared_ptr<T> content_reader::read_object(const std::string& key, const json11::Json& source) noexcept
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
inline std::shared_ptr<T> content_reader::read_object_instance(const std::string& key, const json11::Json& source) noexcept
{
    readers::content_type_reader<T> reader;

    return reader.read(this, key, source);
}

template<>
inline math::matrix4 content_reader::convert(const std::vector<json11::Json>& values) const noexcept
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
inline math::quaternion content_reader::convert(const std::vector<json11::Json>& values) const noexcept
{
    return { static_cast<float>(values[0].number_value())
           , static_cast<float>(values[1].number_value())
           , static_cast<float>(values[2].number_value())
           , static_cast<float>(values[3].number_value()) };
}

template<>
inline math::vector2 content_reader::convert(const std::vector<json11::Json>& values) const noexcept
{
    return { static_cast<float>(values[0].number_value())
           , static_cast<float>(values[1].number_value()) };
}

template<>
inline math::vector3 content_reader::convert(const std::vector<json11::Json>& values) const noexcept
{
    return { static_cast<float>(values[0].number_value())
           , static_cast<float>(values[1].number_value())
           , static_cast<float>(values[2].number_value()) };
}

template<>
inline math::vector4 content_reader::convert(const std::vector<json11::Json>& values) const noexcept
{
    return { static_cast<float>(values[0].number_value())
           , static_cast<float>(values[1].number_value())
           , static_cast<float>(values[2].number_value())
           , static_cast<float>(values[3].number_value()) };
}

}}

#endif // SCENER_CONTENT_CONTENTREADER_HPP
