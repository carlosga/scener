// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Framework/DrawableComponent.hpp>

#include <Framework/Renderer.hpp>

using namespace System;
using namespace SceneR::Framework;
using namespace SceneR::Graphics;

DrawableComponent::DrawableComponent(SceneR::Framework::Renderer& renderer)
    : Component { renderer }
    , visible   { true }
    , drawOrder { 0 }
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

UInt32 DrawableComponent::DrawOrder() const
{
    return this->drawOrder;
}

void DrawableComponent::DrawOrder(const UInt32& drawOrder)
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
