/*
 * EffectParameterCollection.cpp
 *
 *  Created on: Dec 11, 2013
 *      Author: carlos
 */

#include <Graphics/EffectParameterCollection.hpp>
#include <stdexcept>

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

EffectParameter& EffectParameterCollection::operator[](const Int32& parameterIndex)
{
    return this->parameters[parameterIndex];
}

const EffectParameter& EffectParameterCollection::operator[](const Int32& parameterIndex) const
{
    return this->parameters[parameterIndex];
}

EffectParameter& EffectParameterCollection::operator[](const String& parameterName)
{
    auto it = std::find_if(this->parameters.begin(), this->parameters.end(),
                           [&](const EffectParameter& parameter) -> bool
                           {
                               return (parameter.Name() == parameterName);
                           });

    if (it == this->parameters.end())
    {
        throw std::runtime_error("Parameter not found");
    }

    return *it;
}

const EffectParameter& EffectParameterCollection::operator[](const String& parameterName) const
{
    auto it = std::find_if(this->parameters.begin(), this->parameters.end(),
                           [&](const EffectParameter& parameter) -> bool
                           {
                               return parameter.Name() == parameterName;
                           });

    if (it == this->parameters.end())
    {
        throw std::runtime_error("Parameter not found");
    }

    return *it;
}

void EffectParameterCollection::Add(const System::String&                 name,
                                    const EffectParameterClass&           parameterClass,
                                    const EffectParameterType&            parameterType,
                                    const std::shared_ptr<ShaderProgram>& shaderProgram)
{
    this->parameters.push_back({ name, parameterClass, parameterType, shaderProgram });
}
