// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/DirectionalLight.hpp>

using namespace System;
using namespace SceneR::Framework;
using namespace SceneR::Graphics;

DirectionalLight::DirectionalLight()
    : DirectionalLight { Vector3(0.0f, -1.0f, 0.0f), Vector3::One, Vector3::Zero }
{
}

DirectionalLight::DirectionalLight(const Vector3& direction
                                 , const Vector3& diffuseColor
                                 , const Vector3& specularColor)
    : direction     { direction }
    , diffuseColor  { diffuseColor }
    , specularColor { specularColor }
    , enabled       { false }
{
}

DirectionalLight::DirectionalLight(const DirectionalLight& light)
    : direction     { light.direction }
    , diffuseColor  { light.diffuseColor }
    , specularColor { light.specularColor }
    , enabled       { light.enabled }
{
}

DirectionalLight::~DirectionalLight()
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

bool DirectionalLight::Enabled() const
{
    return this->enabled;
}

void DirectionalLight::Enabled(const bool& enabled)
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

DirectionalLight&DirectionalLight::operator=(const DirectionalLight& light)
{
    if (this != &light)
    {
        this->diffuseColor  = light.diffuseColor;
        this->direction     = light.direction;
        this->enabled       = light.enabled;
        this->specularColor = light.specularColor;
    }

    return *this;
}
