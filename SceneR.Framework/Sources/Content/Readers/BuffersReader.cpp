// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/BuffersReader.hpp>

#include <Content/json11.hpp>
#include <Graphics/Buffer.hpp>
#include <Graphics/BufferType.hpp>
#include <Graphics/GraphicsDevice.hpp>
#include <Graphics/Model.hpp>

namespace SceneR
{
    namespace Content
    {
        using json11::Json;
        using SceneR::Graphics::Buffer;
        using SceneR::Graphics::BufferType;
        using SceneR::Graphics::GraphicsDevice;
        using SceneR::Graphics::Model;

        BuffersReader::BuffersReader()
        {
        }

        BuffersReader::~BuffersReader()
        {
        }

        void BuffersReader::read(const json11::Json&               value
                               , SceneR::Graphics::GraphicsDevice& graphicsDevice
                               , SceneR::Graphics::Model*          root)
        {
            for (const auto& item : value["buffers"].object_items())
            {
                auto buffer = std::make_shared<Buffer>();

                buffer->_uri         = item.second["uri"].string_value();
                buffer->_byte_length = item.second["byteLength"].int_value();

                const auto type = item.second["type"].string_value();

                if (type == "arraybuffer")
                {
                    buffer->_type = BufferType::ArrayBuffer;
                }
                else
                {
                    buffer->_type = BufferType::Text;
                }

                root->_buffers[item.first] = buffer;
            }
        }
    }
}