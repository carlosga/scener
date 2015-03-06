// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/Effect.hpp>

#include <cassert>

#include <Graphics/ShaderProgram.hpp>
#include <Graphics/Shader.hpp>

using namespace System;
using namespace SceneR::Graphics;

Effect::Effect(GraphicsDevice& graphicsDevice)
    : GraphicsResource { graphicsDevice }
{
}

Effect::Effect(const Effect& effect)
    : GraphicsResource { effect.graphicsDevice }
    , parameters       { effect.parameters }
    , shader           { effect.shader }
{
}

Effect::~Effect()
{
}

void Effect::Dispose()
{
    if (this->shader)
    {
        this->shader->Dispose();
        this->shader = nullptr;
    }
}

EffectParameterCollection& Effect::Parameters()
{
    return this->parameters;
}

void Effect::Begin()
{
    assert(this->shader != nullptr);

    this->shader->Activate();

    this->OnApply();
}

void Effect::End()
{
    this->shader->Deactivate();
}
