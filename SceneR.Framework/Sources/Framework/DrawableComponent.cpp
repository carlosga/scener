// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Framework/DrawableComponent.hpp>

#include <Framework/Renderer.hpp>

namespace SceneR
{
    namespace Framework
    {
        using SceneR::Graphics::GraphicsDevice;

        DrawableComponent::DrawableComponent(SceneR::Framework::Renderer& renderer)
            : Component { renderer }
            , visible   { true }
            , drawOrder { 0 }
        {
        }

        DrawableComponent::~DrawableComponent()
        {
        }

        void DrawableComponent::Draw(const RenderTime& renderTime)
        {
        }

        GraphicsDevice& DrawableComponent::CurrentGraphicsDevice()
        {
            return this->renderer.CurrentGraphicsDevice();
        }

        bool DrawableComponent::Visible() const
        {
            return this->visible;
        }

        void DrawableComponent::Visible(const bool& visible)
        {
            this->visible = visible;
        }

        std::uint32_t DrawableComponent::DrawOrder() const
        {
            return this->drawOrder;
        }

        void DrawableComponent::DrawOrder(const std::uint32_t& drawOrder)
        {
            this->drawOrder = drawOrder;
        }

        void DrawableComponent::Initialize()
        {
            this->LoadContent();
        }

        void DrawableComponent::LoadContent()
        {
        }

        void DrawableComponent::UnloadContent()
        {
        }
    }
}
