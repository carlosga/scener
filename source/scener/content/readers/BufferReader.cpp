// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/content/readers/BufferReader.hpp"

#include <json11.hpp>

#include "scener/content/ContentReader.hpp"
#include "scener/content/gltf/Buffer.hpp"

namespace scener { namespace content { namespace readers {

using json11::Json;
using scener::content::gltf::Buffer;

auto ContentTypeReader<Buffer>::read(ContentReader* input, const std::string& key, const Json& source) const noexcept
{
    auto buffer = std::make_shared<Buffer>();
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
