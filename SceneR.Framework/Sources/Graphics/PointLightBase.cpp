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

#include <Framework/Color.hpp>
#include <Graphics/PointLightBase.hpp>

using namespace System;
using namespace SceneR::Framework;
using namespace SceneR::Graphics;

const Single& PointLightBase::ConstantAttenuation() const
{
    return this->constantAttenuation;
}

void PointLightBase::ConstantAttenuation(const Single& constantAttenuation)
{
    this->constantAttenuation = constantAttenuation;
}

const Single& PointLightBase::LinearAttenuation() const
{
    return this->linearAttenuation;
}

void PointLightBase::LinearAttenuation(const Single& linearAttenuation)
{
    this->linearAttenuation = linearAttenuation;
}

const Single& PointLightBase::QuadraticAttenuation() const
{
    return this->quadraticAttenuation;
}

void PointLightBase::QuadraticAttenuation(const Single& quadraticAttenuation)
{
    this->quadraticAttenuation = quadraticAttenuation;
}

const Vector3& PointLightBase::Position() const
{
    return this->position;
}

void PointLightBase::Position(const Vector3& position)
{
    this->position = position;
}

const Single& PointLightBase::Range() const
{
    return this->range;
}

void PointLightBase::Range(const Single& range)
{
    this->range = range;
}

const Single PointLightBase::TotalAttenuation(const Single& distance) const
{
    // A = constant_attenuation + ( Dist * linear_attenuation ) + (( Dist^2 ) * quadratic_attenuation )
    return this->constantAttenuation
         + (distance * this->linearAttenuation)
         + ((distance * distance) * this->quadraticAttenuation);
}

PointLightBase::PointLightBase()
    : PointLightBase(SceneR::Framework::Color(1.0f, 1.0f, 1.0f, 1.0f), Vector3(0.0f, 0.0f, 0.0f))
{
}

PointLightBase::PointLightBase(const SceneR::Framework::Color& diffuseColor,
                               const Vector3& position)
    : Light(diffuseColor),
      position(position),
      range(1.0f),
      constantAttenuation(1.0f),
      linearAttenuation(0.0f),
      quadraticAttenuation(0.0f)
{
}
