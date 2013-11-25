//-------------------------------------------------------------------------------
//Copyright 2013 Carlos Guzmán Álvarez
//
//Licensed under the Apache License, Version 2.0 (the "License");
//you may not use this file except in compliance with the License.
//You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//Unless required by applicable law or agreed to in writing, software
//distributed under the License is distributed on an "AS IS" BASIS,
//WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//See the License for the specific language governing permissions and
//limitations under the License.
//-------------------------------------------------------------------------------

#include <Framework/DrawableComponent.hpp>
#include <Framework/Renderer.hpp>
#include <Graphics/GraphicsDevice.hpp>

using namespace System;
using namespace SceneR::Framework;
using namespace SceneR::Graphics;

DrawableComponent::DrawableComponent(Renderer& renderer)
    : Component(renderer),
      visible(true),
      drawOrder(0)
{
}

void DrawableComponent::Draw(const RenderTime& renderTime)
{
}

GraphicsDevice& DrawableComponent::GetGraphicsDevice()
{
    return this->renderer.GetGraphicsDevice();
}

void DrawableComponent::Show()
{
    this->visible = true;
}

void DrawableComponent::Hide()
{
    this->visible = false;
}

const Boolean& DrawableComponent::IsVisible() const
{
    return this->visible;
}

const UInt32& DrawableComponent::GetDrawOrder() const
{
    return this->drawOrder;
}

void DrawableComponent::SetDrawOrder(const UInt32& drawOrder)
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
