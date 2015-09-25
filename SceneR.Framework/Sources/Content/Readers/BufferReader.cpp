// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/BufferReader.hpp>

#include <json11.hpp>
#include <Content/ContentReader.hpp>

namespace SceneR
{
    namespace Content
    {
        using json11::Json;
        using SceneR::Graphics::Buffer;

        std::shared_ptr<Buffer> ContentTypeReader<Buffer>::read(Guide::not_null<ContentReader*>     input
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
