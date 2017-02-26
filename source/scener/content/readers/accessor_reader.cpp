// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/content/readers/accessor_reader.hpp"

#include "scener/content/content_reader.hpp"
#include "scener/content/gltf/accessor.hpp"

namespace scener::content::readers
{
    using nlohmann::json;
    using scener::content::gltf::attribute_type;
    using scener::content::gltf::buffer_view;
    using scener::graphics::component_type;

    auto content_type_reader<gltf::accessor>::read(content_reader* input, const std::string& key, const json& source) const noexcept
    {
        auto        accessor = std::make_shared<gltf::accessor>();
        const auto& type     = source["type"].get<std::string>();

        if (type == "SCALAR")
        {
            accessor->_attribute_type = attribute_type::scalar;
        }
        else if (type == "VEC2")
        {
            accessor->_attribute_type = attribute_type::vector2;
        }
        else if (type == "VEC3")
        {
            accessor->_attribute_type = attribute_type::vector3;
        }
        else if (type == "VEC4")
        {
            accessor->_attribute_type = attribute_type::vector4;
        }
        else if (type == "MAT2")
        {
            accessor->_attribute_type = attribute_type::matrix2;
        }
        else if (type == "MAT3")
        {
            accessor->_attribute_type = attribute_type::matrix3;
        }
        else if (type == "MAT4")
        {
            accessor->_attribute_type = attribute_type::matrix4;
        }

        std::cout << source.dump(4) << std::endl;

        accessor->_name            = key;
        accessor->_component_type  = static_cast<component_type>(source["componentType"].get<std::int32_t>());
        accessor->_byte_offset     = source["byteOffset"].get<std::size_t>();
        accessor->_attribute_count = source["count"].get<std::size_t>();
        accessor->_buffer_view     = input->read_object<buffer_view>(source["bufferView"].get<std::string>());
        accessor->_byte_length     = accessor->_attribute_count
                                   * accessor->get_attribute_type_count()
                                   * accessor->get_component_size_in_bytes();

        if (source.count("byteStride") != 0)
        {
            accessor->_byte_stride = source["byteStride"].get<std::size_t>();
        }

        if (source.count("max") != 0)
        {
            for (const auto& item : source["max"].get<std::vector<float>>())
            {
                accessor->_max.push_back(item);
            }
        }
        if (source.count("min") != 0)
        {
            for (const auto& item : source["min"].get<std::vector<float>>())
            {
                accessor->_min.push_back(item);
            }
        }

        return accessor;
    }
}
