// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/EffectMaterial.hpp>

#include <Graphics/GraphicsDevice.hpp>

using namespace System;
using namespace SceneR::Framework;
using namespace SceneR::Graphics;

EffectMaterial::EffectMaterial(GraphicsDevice& graphicsDevice)
    : Effect { graphicsDevice }
{
    this->Initialize();
}

EffectMaterial::EffectMaterial(const EffectMaterial& effect)
    : Effect { effect }
{
    this->Initialize();
}

EffectMaterial::~EffectMaterial()
{
}

void EffectMaterial::Dispose()
{
    Effect::Dispose();
}

void EffectMaterial::Begin()
{
}

void EffectMaterial::End()
{
}

void EffectMaterial::OnApply()
{
}

void EffectMaterial::Initialize()
{
}
