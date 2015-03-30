// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/EffectParameterCollection.hpp>

#include <cassert>

#include <Graphics/EffectParameter.hpp>
#include <Graphics/UniformBufferObject.hpp>

using namespace System;
using namespace SceneR::Graphics;

EffectParameterCollection::EffectParameterCollection()
{
}

EffectParameterCollection::EffectParameterCollection(const EffectParameterCollection& parameters)
    : parameters { parameters.parameters }
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

EffectParameter& EffectParameterCollection::Add(const System::String&                      name
                                              , const System::UInt32&                      index
                                              , const System::UInt32&                      offset
                                              , const System::UInt32&                      type
                                              , const std::shared_ptr<UniformBufferObject> uniformBuffer)
{
    this->parameters.push_back({ name, index, offset, type, uniformBuffer});

    return (*this)[name];
}

void EffectParameterCollection::Clear()
{
    this->parameters.clear();
}
