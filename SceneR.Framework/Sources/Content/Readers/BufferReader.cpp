// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/BufferReader.hpp>

#include <Content/json11.hpp>
#include <Content/ContentReader.hpp>
#include <Graphics/GraphicsDevice.hpp>
#include <Graphics/Model.hpp>
#include <System/Text/Encoding.hpp>

namespace SceneR
{
    namespace Content
    {
        using json11::Json;
        using SceneR::Graphics::Buffer;
        using SceneR::Graphics::BufferType;
        using SceneR::Graphics::GraphicsDevice;
        using SceneR::Graphics::Model;
        using System::Text::Encoding;

        ContentTypeReader<Buffer>::ContentTypeReader()
        {
        }

        ContentTypeReader<Buffer>::~ContentTypeReader()
        {
        }

        std::shared_ptr<Buffer> ContentTypeReader<Buffer>::read(const std::pair<std::string, Json>& source
                                                              , ContentReaderContext&               context)
        {
            auto buffer = std::make_shared<Buffer>();

            buffer->_name        = Encoding::convert(source.first);
            buffer->_uri         = Encoding::convert(source.second["uri"].string_value());
            buffer->_byte_length = source.second["byteLength"].int_value();

            buffer->set_data(context.content_reader->read_external_reference(buffer->_uri));

            return buffer;
        }
    }
}
