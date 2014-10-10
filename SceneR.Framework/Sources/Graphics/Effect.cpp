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

#include <Graphics/Effect.hpp>
#include <Graphics/Shader.hpp>
#include <Graphics/ShaderProgram.hpp>
#include <cassert>

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

Effect::~Effect()
{
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
