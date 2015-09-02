// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/BufferViewsReader.hpp>

#include <System/IO/BinaryReader.hpp>
#include <GLTF/Model.hpp>
#include <Content/json11.hpp>

namespace SceneR
{
    namespace Content
    {
        using System::IO::BinaryReader;
        using SceneR::GLTF::Buffer;
        using SceneR::GLTF::BufferView;
        using SceneR::GLTF::BufferViewTarget;
        using json11::Json;

        BufferViewsReader::BufferViewsReader()
        {
        }

        BufferViewsReader::~BufferViewsReader()
        {
        }

        void BufferViewsReader::Read(const json11::Json&       value
                                   , System::IO::BinaryReader& reader
                                   , SceneR::GLTF::Model*      root)
        {
            for (const auto& item : value["bufferViews"].object_items())
            {
                auto bufferView = std::make_shared<BufferView>();

                bufferView->buffer     = root->buffers[item.second["buffer"].string_value()];
                bufferView->byteOffset = item.second["byteOffset"].int_value();
                bufferView->byteLength = item.second["byteLength"].int_value();

                const auto& target = value["target"];

                if (target.is_null())
                {
                    bufferView->target = BufferViewTarget::AnimationOrSkin;
                }
                else
                {
                    bufferView->target = static_cast<BufferViewTarget>(target.int_value());
                }

                root->bufferViews.emplace(item.first, bufferView);
            }
        }
    }
}