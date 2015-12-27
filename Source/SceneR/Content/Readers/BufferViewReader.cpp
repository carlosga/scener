// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "BufferViewReader.hpp"

#include <json11.hpp>

#include "Buffer.hpp"
#include "../ContentReader.hpp"

namespace SceneR
{
    namespace Content
    {
        using json11::Json;
        using SceneR::Content::Buffer;
        using SceneR::Content::BufferView;

        std::shared_ptr<BufferView> ContentTypeReader<BufferView>::read(gsl::not_null<ContentReader*>       input
                                                                      , const std::pair<std::string, Json>& source) const
        {
            auto bufferView = std::make_shared<BufferView>();

            bufferView->_name        = source.first;
            bufferView->_buffer      = input->read_object<Buffer>(source.second["buffer"].string_value());
            bufferView->_byte_offset = source.second["byteOffset"].int_value();
            bufferView->_byte_length = source.second["byteLength"].int_value();

            return bufferView;
        }
    }
}
