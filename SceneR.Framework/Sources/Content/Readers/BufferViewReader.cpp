// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/BufferViewReader.hpp>

#include <json11.hpp>
#include <Content/ContentReader.hpp>
#include <Graphics/Buffer.hpp>
#include <Graphics/BufferTarget.hpp>
#include <Graphics/BufferUsage.hpp>
#include <System/Text/Encoding.hpp>

namespace SceneR
{
    namespace Content
    {
        using json11::Json;
        using SceneR::Graphics::Buffer;
        using SceneR::Graphics::BufferTarget;
        using SceneR::Graphics::BufferUsage;
        using SceneR::Graphics::BufferView;
        using System::Text::Encoding;

        ContentTypeReader<BufferView>::ContentTypeReader()
        {
        }

        ContentTypeReader<BufferView>::~ContentTypeReader()
        {
        }

        std::shared_ptr<BufferView> ContentTypeReader<BufferView>::read(ContentReader*                      input
                                                                      , const std::pair<std::string, Json>& source)
        {
            auto bufferTarget = BufferTarget::AnimationOrSkin;
            auto bufferUsage  = BufferUsage::DynamicRead;

            if (!source.second["target"].is_null())
            {
                bufferTarget = static_cast<BufferTarget>(source.second["target"].int_value());
                bufferUsage  = BufferUsage::StaticDraw;
            }

            auto bufferView = std::make_shared<BufferView>(bufferTarget, bufferUsage);

            bufferView->_name        = Encoding::convert(source.first);
            bufferView->_buffer      = input->read_object<Buffer>("buffers", source.second["buffer"].string_value());
            bufferView->_byte_offset = source.second["byteOffset"].int_value();
            bufferView->_byte_length = source.second["byteLength"].int_value();

            return bufferView;
        }
    }
}
