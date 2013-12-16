/*
 * EffectParameterCollection.cpp
 *
 *  Created on: Dec 11, 2013
 *      Author: carlos
 */

#include <Graphics/EffectParameterCollection.hpp>
#include <iostream>

using namespace System;
using namespace SceneR::Graphics;

EffectParameterCollection::EffectParameterCollection()
{
}

EffectParameterCollection::~EffectParameterCollection()
{
}

const System::Size EffectParameterCollection::Count() const
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
    for (auto& p : this->parameters)
    {
        if (p.Name() == parameterName)
        {
            return p;
        }
    }

    throw std::runtime_error("Parameter not found");

//    auto it = std::find_if(this->parameters.begin(), this->parameters.end(),
//                           [&](const EffectParameter& parameter) -> bool
//                           {
//                               return parameter.Name() == parameterName;
//                           });
//
//    if (it == this->parameters.end())
//    {
//        std::cout << "mal mal" << std::endl;
//    }
//
//    return *it;
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
        std::cout << "mal mal" << std::endl;
    }

    return *it;
}

void SceneR::Graphics::EffectParameterCollection::Add(const System::String&       name,
                                                      const EffectParameterClass& parameterClass,
                                                      const EffectParameterType&  parameterType,
                                                      const System::Int32&        parameterLocation)
{
    this->parameters.push_back(EffectParameter(name, parameterClass, parameterType, parameterLocation, nullptr));
}
