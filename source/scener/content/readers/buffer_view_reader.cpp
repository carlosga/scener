// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/content/readers/buffer_view_reader.hpp"

#include "scener/content/content_reader.hpp"
#include "scener/content/gltf/buffer.hpp"
#include "scener/content/gltf/buffer_view.hpp"
#include "scener/content/gltf/constants.hpp"

namespace scener::content::readers
{
    using nlohmann::json;
    using namespace scener::content::gltf;

    auto content_type_reader<buffer_view>::read([[maybe_unused]] content_reader* input, [[maybe_unused]] const std::string& key, const json& value) const noexcept
    {
        auto instance = std::make_shared<buffer_view>();

        instance->_name        = key;
        instance->_buffer      = input->read_object<gltf::buffer>(value[k_buffer].get<std::string>());
        instance->_byte_offset = value[k_byte_offset].get<std::uint32_t>();
        instance->_byte_length = value[k_byte_length].get<std::uint32_t>();

        return instance;
    }
}
