// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "BufferReader.hpp"

#include <json11.hpp>

#include "../ContentReader.hpp"

namespace SceneR
{
    namespace Content
    {
        using json11::Json;
        using SceneR::Content::Buffer;

        std::shared_ptr<Buffer> ContentTypeReader<Buffer>::read(gsl::not_null<ContentReader*>       input
                                                              , const std::pair<std::string, Json>& source) const
        {
            auto buffer = std::make_shared<Buffer>();

            buffer->_name        = source.first;
            buffer->_uri         = source.second["uri"].string_value();
            buffer->_byte_length = source.second["byteLength"].int_value();

            buffer->set_data(input->read_external_reference(buffer->_uri));

            return buffer;
        }
    }
}
