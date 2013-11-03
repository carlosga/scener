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

#include <Graphics/SpotLight.hpp>
#include <stdexcept>

using namespace System;
using namespace SceneR::Framework;
using namespace SceneR::Graphics;

SpotLight::SpotLight()
    : PointLightBase(), direction(0.0f, 0.0f, -1.0f), falloffAngle(180.0f), falloffExponent(0.0f)
{
}

SpotLight::SpotLight(const Color&   diffuseColor,
                     const Vector3& position,
                     const Vector3& direction,
                     const Single&  falloffAngle,
                     const Single&  falloffExponent)
    : PointLightBase(diffuseColor, position),
      direction(direction),
      falloffAngle(falloffAngle),
      falloffExponent(falloffExponent)
{
}

const Vector3& SpotLight::GetDirection() const
{
    return this->direction;
}

void SpotLight::SetDirection(const Vector3& direction)
{
    this->direction = direction;
}

const Single SpotLight::GetFalloffAngle() const
{
    return this->falloffAngle;
}

void SpotLight::SetFalloffAngle(const Single falloffAngle)
{
    if (falloffAngle > 180.0f || falloffAngle < 0.0f)
    {
        throw std::runtime_error("Falloff angle should be between 0 and 180");
    }

    this->falloffAngle = falloffAngle;
}

const Single SpotLight::GetFalloffExponent() const
{
    return this->falloffExponent;
}

void SpotLight::SetFalloffExponent(const Single falloffExponent)
{
    if (falloffExponent > 128.0f || falloffExponent < 0.0f)
    {
        throw std::runtime_error("Falloff angle should be between 0 and 128");
    }

    this->falloffExponent = falloffExponent;
}
