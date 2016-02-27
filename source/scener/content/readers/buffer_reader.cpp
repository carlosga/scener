// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/content/readers/buffer_reader.hpp"

#include <json11.hpp>

#include "scener/content/content_reader.hpp"
#include "scener/content/gltf/buffer.hpp"

namespace scener { namespace content { namespace readers {

using json11::Json;

auto content_type_reader<gltf::buffer>::read(content_reader* input, const std::string& key, const Json& source) const noexcept
{
    auto buffer = std::make_shared<gltf::buffer>();
    auto uri    = source["uri"].string_value();
    auto data   = input->read_external_reference(uri);

    buffer->_name        = key;
    buffer->_uri         = uri;
    buffer->_byte_length = static_cast<std::size_t>(source["byteLength"].int_value());

    Ensures(buffer->_byte_length == data.size());

    buffer->set_data(data);

    return buffer;
}

}}}
