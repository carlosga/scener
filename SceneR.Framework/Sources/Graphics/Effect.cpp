// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/Effect.hpp>

#include <cassert>

#include <Graphics/ShaderProgram.hpp>
#include <Graphics/Shader.hpp>

using namespace System;
using namespace SceneR::Graphics;

Effect::Effect(GraphicsDevice& graphicsDevice
             , const String&   vertexShader
             , const String&   fragmentShader)
    : GraphicsResource { graphicsDevice }
    , parameters       { }
    , shader           { nullptr }
{
    auto vShader = std::make_shared<Shader>(vertexShader, ShaderType::Vertex);
    auto fShader = std::make_shared<Shader>(fragmentShader, ShaderType::Fragment);
    auto shaders = std::vector<std::shared_ptr<Shader>>{};

    shaders.push_back(vShader);
    shaders.push_back(fShader);

    this->shader = std::make_shared<ShaderProgram>(shaders);
    this->shader->Build();
}

Effect::Effect(const Effect& effect)
    : GraphicsResource { effect.graphicsDevice }
    , parameters       { effect.parameters }
    , shader           { effect.shader }
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
