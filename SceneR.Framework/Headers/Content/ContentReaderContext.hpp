// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef CONTENTREADERCONTEXT_HPP
#define CONTENTREADERCONTEXT_HPP

#include <memory>
#include <string>
#include <vector>

namespace SceneR
{
    namespace Graphics
    {
        class Accessor;
        class BufferView;
        class Effect;
        class GraphicsDevice;
        class Material;
        class Model;
    }
}

namespace SceneR
{
    namespace Content
    {
        class ContentReaderContext
        {
        public:
            ContentReaderContext(SceneR::Graphics::GraphicsDevice& graphicsDevice);
            ~ContentReaderContext();

        public:
            std::shared_ptr<SceneR::Graphics::BufferView> find_buffer_view(const std::u16string& name) const;

            std::shared_ptr<SceneR::Graphics::Accessor> find_accessor(const std::u16string& name) const;

            std::shared_ptr<SceneR::Graphics::Material> find_material(const std::u16string& name) const;

            std::shared_ptr<SceneR::Graphics::Effect> find_effect(const std::u16string& name) const;

        public:
            SceneR::Graphics::GraphicsDevice&                          graphics_device;
            std::shared_ptr<SceneR::Graphics::Model>                   model;
            std::vector<std::shared_ptr<SceneR::Graphics::Accessor>>   accessors;
            std::vector<std::shared_ptr<SceneR::Graphics::BufferView>> buffer_views;
            std::vector<std::shared_ptr<SceneR::Graphics::Effect>>     effects;
            std::vector<std::shared_ptr<SceneR::Graphics::Material>>   materials;
        };
    }
}

#endif // CONTENTREADERCONTEXT_HPP
