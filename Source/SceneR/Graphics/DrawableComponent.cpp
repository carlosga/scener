// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "DrawableComponent.hpp"

#include "Renderer.hpp"

namespace SceneR
{
    namespace Graphics
    {
        DrawableComponent::DrawableComponent(gsl::not_null<Renderer*> renderer)
            : Component { renderer }
        {
        }

        GraphicsDevice* DrawableComponent::graphics_device() noexcept
        {
            return _renderer->graphics_device();
        }

        void DrawableComponent::draw(const StepTime& renderTime)
        {
        }

        bool DrawableComponent::visible() const noexcept
        {
            return _visible;
        }

        void DrawableComponent::visible(const bool& visible) noexcept
        {
            _visible = visible;
        }

        std::uint32_t DrawableComponent::draw_order() const noexcept
        {
            return _draw_order;
        }

        void DrawableComponent::draw_order(const std::uint32_t& drawOrder) noexcept
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
