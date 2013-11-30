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

#include <Graphics/Light.hpp>

using namespace SceneR::Framework;
using namespace SceneR::Graphics;

const Color& Light::Color() const
{
    return this->color;
}

void Light::Color(const SceneR::Framework::Color& color)
{
    this->color = color;
}

Light::Light()
    : object(0), color(1.0f, 1.0f, 1.0f, 1.0f)
{
}

Light::Light(const SceneR::Framework::Color& color)
    : object(0), color(color)
{
}

Light::~Light()
{
}
