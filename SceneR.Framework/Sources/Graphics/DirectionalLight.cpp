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

#include <Graphics/DirectionalLight.hpp>

using namespace SceneR::Framework;
using namespace SceneR::Graphics;

DirectionalLight::DirectionalLight()
    : Light(), direction(0.0f, 0.0f, -1.0f)
{
}

DirectionalLight::DirectionalLight(const Vector3&                  direction,
                                   const SceneR::Framework::Color& diffuseColor,
                                   const SceneR::Framework::Color& specularColor)
    : Light(diffuseColor),
      direction(direction),
      specularColor(specularColor)
{
}

const Vector3& DirectionalLight::Direction() const
{
    return this->direction;
}

void DirectionalLight::Direction(const Vector3& direction)
{
    this->direction = direction;
}

const SceneR::Framework::Color& DirectionalLight::SpecularColor() const
{
    return this->specularColor;
}

void DirectionalLight::SpecularColor(const SceneR::Framework::Color& specularColor)
{
    this->specularColor = specularColor;
}
