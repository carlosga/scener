// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SceneR/Content/Readers/BufferViewReader.hpp"

#include <json11.hpp>

#include "SceneR/Content/ContentReader.hpp"
#include "SceneR/Content/GLTF/Buffer.hpp"
#include "SceneR/Content/GLTF/BufferView.hpp"

namespace SceneR { namespace Content { namespace Readers {

using json11::Json;
using SceneR::Content::GLTF::Buffer;
using SceneR::Content::GLTF::BufferView;

auto ContentTypeReader<BufferView>::read(ContentReader* input, const std::string& key, const Json& source) const noexcept
{
    auto bufferView = std::make_shared<BufferView>();

    bufferView->_name        = key;
    bufferView->_buffer      = input->read_object<Buffer>(source["buffer"].string_value());
    bufferView->_byte_offset = static_cast<std::size_t>(source["byteOffset"].int_value());
    bufferView->_byte_length = static_cast<std::size_t>(source["byteLength"].int_value());

    return bufferView;
}

}}}
