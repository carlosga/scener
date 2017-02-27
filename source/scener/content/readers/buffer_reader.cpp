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

    auto content_type_reader<gltf::buffer>::read(content_reader* input, const std::string& key, const json& source) const noexcept
    {
        auto buffer = std::make_shared<gltf::buffer>();
        auto uri    = source[k_uri].get<std::string>();
        auto data   = input->read_external_reference(uri);

        buffer->_name        = key;
        buffer->_uri         = uri;
        buffer->_byte_length = source[k_byte_length].get<std::size_t>();

        Ensures(buffer->_byte_length == data.size());

        buffer->set_data(data);

        return buffer;
    }
}
