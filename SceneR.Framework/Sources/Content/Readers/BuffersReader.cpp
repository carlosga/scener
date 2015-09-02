// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/BuffersReader.hpp>

#include <iostream>

#include <System/IO/BinaryReader.hpp>
#include <Content/json11.hpp>
#include <GLTF/Model.hpp>

namespace SceneR
{
    namespace Content
    {
        using json11::Json;
        using SceneR::GLTF::Model;
        using SceneR::GLTF::Buffer;
        using SceneR::GLTF::BufferType;

        BuffersReader::BuffersReader()
        {
        }

        BuffersReader::~BuffersReader()
        {
        }

        void BuffersReader::Read(const json11::Json&       value
                               , System::IO::BinaryReader& reader
                               , SceneR::GLTF::Model*      root)
        {
            for (const auto& item : value["buffers"].object_items())
            {
                auto buffer = std::make_shared<Buffer>();

                std::cout << item.second.dump() << std::endl;

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
