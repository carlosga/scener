// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/content/readers/accessor_reader.hpp"

#include "scener/content/content_reader.hpp"
#include "scener/content/gltf/accessor.hpp"
#include "scener/content/gltf/constants.hpp"

namespace scener::content::readers
{
    using nlohmann::json;
    using namespace scener::content::gltf;

    auto content_type_reader<accessor>::read(content_reader* input, const std::string& key, const json& value) const noexcept
    {
        auto        instance = std::make_shared<accessor>();
        const auto& type     = value[k_type].get<std::string>();

        if (type == k_scalar)
        {
            instance->_attribute_type = attribute_type::scalar;
        }
        else if (type == k_vec2)
        {
            instance->_attribute_type = attribute_type::vector2;
        }
        else if (type == k_vec3)
        {
            instance->_attribute_type = attribute_type::vector3;
        }
        else if (type == k_vec4)
        {
            instance->_attribute_type = attribute_type::vector4;
        }
        else if (type == k_mat2)
        {
            instance->_attribute_type = attribute_type::matrix2;
        }
        else if (type == k_mat3)
        {
            instance->_attribute_type = attribute_type::matrix3;
        }
        else if (type == k_mat4)
        {
            instance->_attribute_type = attribute_type::matrix4;
        }

        instance->_name            = key;
        instance->_component_type  = static_cast<component_type>(value[k_component_type].get<std::int32_t>());
        instance->_byte_offset     = value[k_byte_offset].get<std::size_t>();
        instance->_attribute_count = value[k_count].get<std::size_t>();
        instance->_buffer_view     = input->read_object<buffer_view>(value[k_buffer_view].get<std::string>());
        instance->_byte_length     = instance->_attribute_count
                                   * instance->get_attribute_type_count()
                                   * instance->get_component_size_in_bytes();

        if (value.count(k_byte_stride) != 0)
        {
            instance->_byte_stride = value[k_byte_stride].get<std::size_t>();
        }

        if (value.count(k_max) != 0)
        {
            for (const auto& item : value[k_max].get<std::vector<float>>())
            {
                instance->_max.push_back(item);
            }
        }
        if (value.count(k_min) != 0)
        {
            for (const auto& item : value[k_min].get<std::vector<float>>())
            {
                instance->_min.push_back(item);
            }
        }

        return instance;
    }
}
