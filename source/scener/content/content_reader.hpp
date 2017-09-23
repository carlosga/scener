// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_CONTENT_CONTENT_READER_HPP
#define SCENER_CONTENT_CONTENT_READER_HPP

#include <any>
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "json.hpp"

#include "scener/content/readers/content_type_reader.hpp"
#include "scener/content/gltf/node.hpp"
#include "scener/graphics/bone.hpp"
#include "scener/io/binary_reader.hpp"
#include "scener/io/stream.hpp"
#include "scener/math/matrix.hpp"
#include "scener/math/quaternion.hpp"
#include "scener/math/vector.hpp"

namespace scener::content::dds { class surface; }

namespace scener::content::gltf
{
    class accessor;
    class buffer;
    class buffer_view;
}

namespace scener::graphics
{
    class effect_technique;
    class model;
    class model_mesh;
    class sampler_state;
    class texture2d;

    namespace vulkan
    {
        class shader_module;
        class shader;
    }
}

namespace scener::content
{
    class content_manager;

    /// Reads application content_manager from disk.
    class content_reader final
    {
    public:
        /// Initializes a new instance of the content_reader.
        /// \param assetname the name of the asset to be readed.
        /// \param manager the content_manager that owns this content_reader.
        /// \param stream the base stream.
        content_reader(const std::string& assetname, content::content_manager* manager, io::stream& stream) noexcept;

        /// Releases all resources used by the current instance of the content_reader class.
        ~content_reader() = default;

    public:
        /// Gets the name of the asset currently being read by this content_reader.
        const std::string& asset_name() const noexcept;

        /// Gets the content manager that owns this content_reader.
        content::content_manager* content_manager() const noexcept;

    public:
        /// Reads the contents of the current asset.
        /// \returns the contents of the current asset.
        std::shared_ptr<graphics::model> read_asset() noexcept;

    private:
        bool read_header() noexcept;

        std::string get_asset_path(const std::string& assetname) const noexcept;

        std::vector<std::uint8_t> read_external_reference(const std::string& assetname) const noexcept;

    private:
        template<typename T>
        inline std::shared_ptr<T> read_object(const std::string& key) noexcept;

        template<typename T>
        inline std::shared_ptr<T> read_object(const std::string& key, const nlohmann::json& value) noexcept
        {
            auto instance = get_object<T>(key);
            if (instance != nullptr)
            {
                return instance;
            }

            auto object = read_object_instance<T>(key, value);

            cache_object<T>(key, object);

            return object;
        }

        template<typename T>
        inline std::shared_ptr<T> read_object_instance(const std::string& key) noexcept;

        template<typename T>
        inline std::shared_ptr<T> read_object_instance(const std::string& key, const nlohmann::json& value) noexcept
        {
            readers::content_type_reader<T> reader;

            return reader.read(this, key, value);
        }

        template <typename T>
        inline std::shared_ptr<T> get_object(const std::string& key) noexcept
        {
            if (_cache.find(key) != _cache.end())
            {
                return std::any_cast<std::shared_ptr<T>>(_cache[key]);
            }

            return nullptr;
        }

        template <typename T>
        inline void cache_object(const std::string& key, std::shared_ptr<T> object) noexcept
        {
            _cache[key] = object;
        }

        template <typename T>
        inline T convert(const std::vector<nlohmann::json>& values) const noexcept;

    private:
        std::string                               _asset_name;
        io::binary_reader                         _asset_reader;
        content::content_manager*                 _content_manager;
        nlohmann::json                            _root;
        std::unordered_map<std::string, std::any> _cache;

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

    // Buffers
    template<>
    inline std::shared_ptr<gltf::buffer> content_reader::read_object(const std::string& key) noexcept
    {
        return read_object<gltf::buffer>(key, _root["buffers"][key]);
    }

    // Buffer Views
    template<>
    inline std::shared_ptr<gltf::buffer_view> content_reader::read_object(const std::string& key) noexcept
    {
        return read_object<gltf::buffer_view>(key, _root["bufferViews"][key]);
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

    // Meshes
    template<>
    inline std::shared_ptr<graphics::model_mesh> content_reader::read_object(const std::string& key) noexcept
    {
        return read_object<graphics::model_mesh>(key, _root["meshes"][key]);
    }

    // Nodes
    template<>
    inline std::shared_ptr<gltf::node> content_reader::read_object(const std::string& key) noexcept
    {
        return read_object<gltf::node>(key, _root["nodes"][key]);
    }

    // Samplers
    template<>
    inline std::shared_ptr<graphics::sampler_state> content_reader::read_object(const std::string& key) noexcept
    {
        return read_object<graphics::sampler_state>(key, _root["samplers"][key]);
    }

    // Shaders
    template<>
    inline std::shared_ptr<graphics::vulkan::shader> content_reader::read_object(const std::string& key) noexcept
    {
        return read_object<graphics::vulkan::shader>(key, _root["shaders"][key]);
    }

    // Textures
    template<>
    inline std::shared_ptr<graphics::texture2d> content_reader::read_object(const std::string& key) noexcept
    {
        return read_object<graphics::texture2d>(key, _root["textures"][key]);
    }

    // Type conversion operations
    template<>
    inline math::matrix4 content_reader::convert(const std::vector<nlohmann::json>& values) const noexcept
    {
        math::matrix4 matrix;

        for (std::size_t i = 0; i < 4; ++i)
        {
            for (std::size_t j = 0; j < 4; ++j)
            {
                matrix[i][j] = values[i * 4 + j].get<float>();
            }
        }

        return matrix;
    }

    template<>
    inline math::quaternion content_reader::convert(const std::vector<nlohmann::json>& values) const noexcept
    {
        return { values[0].get<float>()
               , values[1].get<float>()
               , values[2].get<float>()
               , values[3].get<float>() };
    }

    template<>
    inline math::vector2 content_reader::convert(const std::vector<nlohmann::json>& values) const noexcept
    {
        return { values[0].get<float>()
               , values[1].get<float>() };
    }

    template<>
    inline math::vector3 content_reader::convert(const std::vector<nlohmann::json>& values) const noexcept
    {
        return { values[0].get<float>()
               , values[1].get<float>()
               , values[2].get<float>() };
    }

    template<>
    inline math::vector4 content_reader::convert(const std::vector<nlohmann::json>& values) const noexcept
    {
        return { values[0].get<float>()
               , values[1].get<float>()
               , values[2].get<float>()
               , values[3].get<float>() };
    }
}

#endif // SCENER_CONTENT_CONTENT_READER_HPP
