// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/content/readers/buffer_reader.hpp"

#include "scener/content/content_reader.hpp"
#include "scener/content/gltf/buffer.hpp"
#include "scener/content/gltf/constants.hpp"

namespace scener::content::readers
{
    using nlohmann::json;
    using namespace scener::content::gltf;

    auto content_type_reader<buffer>::read([[maybe_unused]] content_reader* input, [[maybe_unused]] const std::string& key, const json& value) const noexcept
    {
        auto instance = std::make_shared<buffer>();
        auto uri      = value[k_uri].get<std::string>();

        instance->_name        = key;
        instance->_uri         = uri;
        instance->_byte_length = value[k_byte_length].get<std::uint32_t>();

        instance->set_data(input->read_external_reference(uri));

        return instance;
    }
}
