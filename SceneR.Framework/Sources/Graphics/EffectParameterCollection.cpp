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

#include <Graphics/EffectParameter.hpp>
#include <Graphics/EffectParameterCollection.hpp>
#include <Graphics/ShaderProgram.hpp>
#include <algorithm>
#include <cassert>

using namespace System;
using namespace SceneR::Graphics;

EffectParameterCollection::EffectParameterCollection()
{
}

EffectParameterCollection::EffectParameterCollection(const EffectParameterCollection& parameters)
    : parameters(parameters.parameters)
{
}

EffectParameterCollection::~EffectParameterCollection()
{
}

System::Size EffectParameterCollection::Count() const
{
    return this->parameters.size();
}

EffectParameter& EffectParameterCollection::operator[](const Size& parameterIndex)
{
    assert(parameterIndex < this->parameters.size());

    return this->parameters[parameterIndex];
}

const EffectParameter& EffectParameterCollection::operator[](const Size& parameterIndex) const
{
    assert(parameterIndex < this->parameters.size());

    return this->parameters[parameterIndex];
}

EffectParameter& EffectParameterCollection::operator[](const String& parameterName)
{
    auto it = std::find_if(this->parameters.begin(), this->parameters.end(),
                           [&](const EffectParameter& parameter) -> bool
                           {
                               return (parameter.Name() == parameterName);
                           });

    assert (it != this->parameters.end());

    return *it;
}

const EffectParameter& EffectParameterCollection::operator[](const String& parameterName) const
{
    auto it = std::find_if(this->parameters.begin(), this->parameters.end(),
                           [&](const EffectParameter& parameter) -> bool
                           {
                               return parameter.Name() == parameterName;
                           });

    assert (it != this->parameters.end());

    return *it;
}

EffectParameter& EffectParameterCollection::Add(const System::String&                 name
                                              , const EffectParameterClass&           parameterClass
                                              , const EffectParameterType&            parameterType
                                              , const std::shared_ptr<ShaderProgram>& shader)
{
    this->parameters.push_back({ name, parameterClass, parameterType, shader });

    return (*this)[name];
}
