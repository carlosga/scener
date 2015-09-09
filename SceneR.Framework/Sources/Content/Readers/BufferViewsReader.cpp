// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/BufferViewsReader.hpp>

#include <Content/json11.hpp>
#include <Graphics/Buffer.hpp>
#include <Graphics/BufferTarget.hpp>
#include <Graphics/BufferUsage.hpp>
#include <Graphics/BufferView.hpp>
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

        BufferViewsReader::BufferViewsReader()
        {
        }

        BufferViewsReader::~BufferViewsReader()
        {
        }

        void BufferViewsReader::read(const json11::Json& value, ContentReaderContext& context)
        {
            for (const auto& item : value["bufferViews"].object_items())
            {
                auto bufferTarget = BufferTarget::AnimationOrSkin;
                auto bufferUsage  = BufferUsage::DynamicRead;

                if (!item.second["target"].is_null())
                {
                    bufferTarget = static_cast<BufferTarget>(item.second["target"].int_value());
                    bufferUsage  = BufferUsage::StaticDraw;
                }

                auto bufferView = std::make_shared<BufferView>(bufferTarget, bufferUsage);

                bufferView->_name        = Encoding::convert(item.first);
                bufferView->_buffer      = context.find_object<Buffer>(item.second["buffer"].string_value());
                bufferView->_byte_offset = item.second["byteOffset"].int_value();
                bufferView->_byte_length = item.second["byteLength"].int_value();

                context.buffer_views.push_back(bufferView);
            }
        }
    }
}
