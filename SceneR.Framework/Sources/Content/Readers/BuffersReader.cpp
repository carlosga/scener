// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/BuffersReader.hpp>

#include <Content/json11.hpp>
#include <Graphics/Buffer.hpp>
#include <Graphics/BufferType.hpp>
#include <Graphics/Model.hpp>

namespace SceneR
{
    namespace Content
    {
        using json11::Json;
        using SceneR::Graphics::Model;
        using SceneR::Graphics::Buffer;
        using SceneR::Graphics::BufferType;

        BuffersReader::BuffersReader()
        {
        }

        BuffersReader::~BuffersReader()
        {
        }

        void BuffersReader::Read(const json11::Json& value, SceneR::Graphics::Model* root)
        {
            for (const auto& item : value["buffers"].object_items())
            {
                auto buffer = std::make_shared<Buffer>();

                buffer->uri        = item.second["uri"].string_value();
                buffer->byteLength = item.second["byteLength"].int_value();

                const auto type = item.second["type"].string_value();

                if (type == "arraybuffer")
                {
                    buffer->type = BufferType::ArrayBuffer;
                }
                else
                {
                    buffer->type = BufferType::Text;
                }

                root->buffers[item.first] = buffer;
            }
        }
    }
}
