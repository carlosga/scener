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

#include <Framework/Component.hpp>
#include <Framework/Renderer.hpp>

using namespace System;
using namespace SceneR::Framework;

Component::Component(SceneR::Framework::Renderer& renderer)
    : renderer(renderer),
      enabled(true),
      updateOrder(0)
{
}

Component::~Component()
{
}

SceneR::Framework::Renderer& Component::Renderer()
{
    return this->renderer;
}

//void Component::Update(const RenderTime& renderTime)
//{
//}

const Boolean& Component::Enabled() const
{
    return this->enabled;
}

void Component::Enabled(const Boolean& enabled)
{
    this->enabled = enabled;
}

const UInt32& Component::UpdateOrder() const
{
    return this->updateOrder;
}

void Component::UpdateOrder(const UInt32& updateOrder)
{
    this->updateOrder = updateOrder;
}
