// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/BufferViewsReader.hpp>

#include <Content/json11.hpp>
#include <Graphics/Buffer.hpp>
#include <Graphics/BufferTarget.hpp>
#include <Graphics/BufferUsage.hpp>
#include <Graphics/BufferView.hpp>
#include <Graphics/Model.hpp>

namespace SceneR
{
    namespace Content
    {
        using SceneR::Graphics::Buffer;
        using SceneR::Graphics::BufferView;
        using SceneR::Graphics::BufferTarget;
        using SceneR::Graphics::BufferUsage;
        using json11::Json;

        BufferViewsReader::BufferViewsReader()
        {
        }

        BufferViewsReader::~BufferViewsReader()
        {
        }

        void BufferViewsReader::Read(const json11::Json& value, SceneR::Graphics::Model* root)
        {
            for (const auto& item : value["bufferViews"].object_items())
            {
                auto bufferTarget = BufferTarget::AnimationOrSkin;
                auto bufferUsage  = BufferUsage::DynamicRead;

                if (!item.second["target"].is_null())
                {
                    bufferTarget = static_cast<BufferTarget>(item.second["target"].int_value());
                    bufferUsage  = BufferUsage::DynamicDraw;
                }

                auto bufferView = std::make_shared<BufferView>(bufferTarget, bufferUsage);

                bufferView->buffer     = root->buffers[item.second["buffer"].string_value()];
                bufferView->byteOffset = item.second["byteOffset"].int_value();
                bufferView->byteLength = item.second["byteLength"].int_value();

                root->bufferViews[item.first] = bufferView;
            }
        }
    }
}
