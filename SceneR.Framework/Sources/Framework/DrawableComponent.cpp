// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Framework/DrawableComponent.hpp>

#include <Framework/Renderer.hpp>

namespace SceneR
{
    namespace Framework
    {
        using SceneR::Graphics::GraphicsDevice;

        DrawableComponent::DrawableComponent(Renderer* renderer)
            : Component   { renderer }
            , _visible    { true }
            , _draw_order { 0 }
        {
        }

        GraphicsDevice* DrawableComponent::graphics_device()
        {
            return _renderer->graphics_device();
        }

        void DrawableComponent::draw(const RenderTime& renderTime)
        {
        }

        bool DrawableComponent::visible() const
        {
            return _visible;
        }

        void DrawableComponent::visible(const bool& visible)
        {
            _visible = visible;
        }

        std::uint32_t DrawableComponent::draw_order() const
        {
            return _draw_order;
        }

        void DrawableComponent::draw_order(const std::uint32_t& drawOrder)
        {
            _draw_order = drawOrder;
        }

        void DrawableComponent::initialize()
        {
            this->load_content();
        }

        void DrawableComponent::load_content()
        {
        }

        void DrawableComponent::unload_content()
        {
        }
    }
}
