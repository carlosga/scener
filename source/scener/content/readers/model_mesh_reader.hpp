// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_CONTENT_READERS_MODEL_MESH_READER_HPP
#define SCENER_CONTENT_READERS_MODEL_MESH_READER_HPP

#include "scener/content/readers/content_type_reader.hpp"

namespace scener::graphics
{
    enum class vertex_element_format : std::uint32_t;
    enum class vertex_element_usage  : std::uint32_t;

    class effect_technique;
    class model_mesh;
    class model_mesh_part;
}

namespace scener::content::gltf { enum class attribute_type : std::uint32_t; }

namespace scener::content::readers
{
    template<>
    class content_type_reader<graphics::model_mesh>
    {
    public:
        content_type_reader() = default;

    public:
        auto read([[maybe_unused]] content_reader* input, [[maybe_unused]] const std::string& key, const nlohmann::json& value) const noexcept;

    private:
        std::shared_ptr<graphics::model_mesh_part> read_mesh_part(content_reader* input, const nlohmann::json& value) const noexcept;

        std::shared_ptr<graphics::effect_technique> read_material(content_reader* input, const std::string& key) const noexcept;

        graphics::vertex_element_format get_vertex_element_format(gltf::attribute_type type) const noexcept;

        graphics::vertex_element_usage get_vertex_element_usage(const std::string& semantic) const noexcept;
    };
}

#endif  // SCENER_CONTENT_READERS_MODEL_MESH_READER_HPP
