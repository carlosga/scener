// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SceneR/Content/Readers/BufferReader.hpp"

#include <json11.hpp>

#include "SceneR/Content/ContentReader.hpp"
#include "SceneR/Content/GLTF/Buffer.hpp"

namespace SceneR { namespace Content { namespace Readers {

using json11::Json;
using SceneR::Content::GLTF::Buffer;

auto ContentTypeReader<Buffer>::read(ContentReader* input, const std::string& key, const Json& source) const noexcept
{
    auto buffer = std::make_shared<Buffer>();

    buffer->_name        = key;
    buffer->_uri         = source["uri"].string_value();
    buffer->_byte_length = source["byteLength"].int_value();

    buffer->set_data(input->read_external_reference(buffer->_uri));

    return buffer;
}

}}}
