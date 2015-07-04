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

size_t EffectParameterCollection::Count() const
{
    return this->parameters.size();
}

EffectParameter& EffectParameterCollection::operator[](const size_t& parameterIndex)
{
    assert(parameterIndex < this->parameters.size());

    return this->parameters[parameterIndex];
}

const EffectParameter& EffectParameterCollection::operator[](const size_t& parameterIndex) const
{
    assert(parameterIndex < this->parameters.size());

    return this->parameters[parameterIndex];
}

EffectParameter& EffectParameterCollection::operator[](const std::u16string& parameterName)
{
    auto it = std::find_if(this->parameters.begin(), this->parameters.end(),
                           [&](const EffectParameter& parameter) -> bool
                           {
                               return (parameter.Name() == parameterName);
                           });

    assert (it != this->parameters.end());

    return *it;
}

const EffectParameter& EffectParameterCollection::operator[](const std::u16string& parameterName) const
{
    auto it = std::find_if(this->parameters.begin(), this->parameters.end(),
                           [&](const EffectParameter& parameter) -> bool
                           {
                               return parameter.Name() == parameterName;
                           });

    assert (it != this->parameters.end());

    return *it;
}

EffectParameter& EffectParameterCollection::Add(const std::u16string&                      name
                                              , const std::size_t&                         index
                                              , const std::size_t&                         offset
                                              , const std::uint32_t&                       type
                                              , const std::shared_ptr<UniformBufferObject> uniformBuffer)
{
    this->parameters.push_back({ name, index, offset, type, uniformBuffer});

    return (*this)[name];
}

void EffectParameterCollection::Clear()
{
    this->parameters.clear();
}
