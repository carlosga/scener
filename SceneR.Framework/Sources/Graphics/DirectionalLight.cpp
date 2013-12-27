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

using namespace System;
using namespace SceneR::Framework;
using namespace SceneR::Graphics;

DirectionalLight::DirectionalLight()
    : DirectionalLight(Vector3::One, Vector3(0.0f, -1.0f, 0.0f), true, Vector3::Zero)
{
}

DirectionalLight::DirectionalLight(const Vector3& diffuseColor,
                                   const Vector3& direction,
                                   const Boolean& enabled,
                                   const Vector3& specularColor)
    : diffuseColor(diffuseColor),
      direction(direction),
      enabled(enabled),
      specularColor(specularColor)
{
}

const Vector3& DirectionalLight::DiffuseColor() const
{
    return this->diffuseColor;
}

void DirectionalLight::DiffuseColor(const Vector3& diffuseColor)
{
    this->diffuseColor = diffuseColor;
}

const Vector3& DirectionalLight::Direction() const
{
    return this->direction;
}

void DirectionalLight::Direction(const Vector3& direction)
{
    this->direction = direction;
}

const Boolean& DirectionalLight::Enabled() const
{
    return this->enabled;
}

void DirectionalLight::Enabled(const System::Boolean& enabled)
{
    this->enabled = enabled;
}

const Vector3& DirectionalLight::SpecularColor() const
{
    return this->specularColor;
}

void DirectionalLight::SpecularColor(const Vector3& specularColor)
{
    this->specularColor = specularColor;
}
