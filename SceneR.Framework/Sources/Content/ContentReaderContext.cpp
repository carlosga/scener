// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/ContentReaderContext.hpp>

#include <Graphics/Accessor.hpp>
#include <Graphics/BufferView.hpp>
#include <Graphics/Effect.hpp>
#include <Graphics/GraphicsDevice.hpp>
#include <Graphics/Material.hpp>

using SceneR::Graphics::Accessor;
using SceneR::Graphics::BufferView;
using SceneR::Graphics::Effect;
using SceneR::Graphics::GraphicsDevice;
using SceneR::Graphics::Material;

namespace SceneR
{
    namespace Content
    {
        ContentReaderContext::ContentReaderContext(GraphicsDevice& graphicsDevice)
            : graphics_device (graphicsDevice)
            , accessors       ()
            , buffer_views    ()
            , effects         ()
            , materials       ()
        {
        }

        ContentReaderContext::~ContentReaderContext()
        {
        }

        std::shared_ptr<BufferView> ContentReaderContext::find_buffer_view(const std::u16string& name) const
        {
            auto it = find_if(buffer_views.begin()
                            , buffer_views.end()
                            , [&](std::shared_ptr<BufferView> bufferView) -> bool
                {
                    return (bufferView->name() == name);
                });

            return ((it != buffer_views.end()) ? *it : nullptr);
        }

        std::shared_ptr<Accessor> ContentReaderContext::find_accessor(const std::u16string& name) const
        {
            auto it = find_if(accessors.begin()
                            , accessors.end()
                            , [&](std::shared_ptr<Accessor> accessor) -> bool
                {
                    return (accessor->name() == name);
                });

            return ((it != accessors.end()) ? *it : nullptr);
        }

        std::shared_ptr<Material> ContentReaderContext::find_material(const std::u16string& name) const
        {
            auto it = find_if(materials.begin()
                            , materials.end()
                            , [&](std::shared_ptr<Material> material) -> bool
                {
                    return (material->name() == name);
                });

            return ((it != materials.end()) ? *it : nullptr);
        }

        std::shared_ptr<Effect> ContentReaderContext::find_effect(const std::u16string &name) const
        {
            auto it = find_if(effects.begin()
                            , effects.end()
                            , [&](std::shared_ptr<Effect> effect) -> bool
                {
                    return (effect->name == name);
                });

            return ((it != effects.end()) ? *it : nullptr);
        }
    }
}
