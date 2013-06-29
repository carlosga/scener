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

#include "Graphics/PointLightBase.hpp"

using namespace SceneR::Core;
using namespace SceneR::Graphics;

PointLightBase::PointLightBase()
    : PointLightBase(Color(1.0f, 1.0f, 1.0f, 1.0f),
      Vector3(0.0f, 0.0f, 0.0f))
{
}

PointLightBase::PointLightBase(const Color& diffuseColor, const Vector3& position)
    : Light(diffuseColor),
      position(position),
      range(1.0f),
      constantAttenuation(1.0f),
      linearAttenuation(0.0f),
      quadraticAttenuation(0.0f)
{
}

const Single PointLightBase::GetConstantAttenuation() const
{
    return this->constantAttenuation;
}            

void PointLightBase::SetConstantAttenuation(const Single constantAttenuation)
{
    this->constantAttenuation = constantAttenuation;
}

const Single PointLightBase::GetLinearAttenuation() const
{
    return this->linearAttenuation;
}

void PointLightBase::SetLinearAttenuation(const Single linearAttenuation)
{
    this->linearAttenuation = linearAttenuation;
}

const Single PointLightBase::GetQuadraticAttenuation() const
{
    return this->quadraticAttenuation;
}

void PointLightBase::SetQuadraticAttenuation(const Single quadraticAttenuation)
{
    this->quadraticAttenuation = quadraticAttenuation;
}

const Vector3& PointLightBase::GetPosition() const
{
    return this->position;
}

void PointLightBase::SetPosition(const Vector3& position)
{
    this->position = position;
}

const Single PointLightBase::GetRange() const
{
    return this->range;
}

void PointLightBase::SetRange(const Single range)
{
    this->range = range;
}

const Single PointLightBase::GetTotalAttenuation(const Single distance) const
{
    // A = constant_attenuation + ( Dist * linear_attenuation ) + (( Dist^2 ) * quadratic_attenuation )  
    return this->constantAttenuation + (distance * this->linearAttenuation) + ((distance * distance) * this->quadraticAttenuation);
}
