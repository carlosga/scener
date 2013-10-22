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

#include <stdexcept>
#include "Graphics/Effect.hpp"

using namespace SceneR::Graphics;

Effect::Effect(GraphicsDevice& graphicsDevice)
    : GraphicsResource(graphicsDevice),
      parameters(0),
      shaderProgram(nullptr)
{
}

Effect::Effect(const Effect& effect)
    : GraphicsResource(effect.graphicsDevice),
      parameters(effect.parameters),
      shaderProgram(effect.shaderProgram)
{
}

Effect::~Effect()
{
}

const std::vector<EffectParameter>& Effect::Parameters() const
{
    return this->parameters;
}

void Effect::Begin()
{
    if (this->shaderProgram == nullptr)
    {
        throw std::runtime_error("Shader program not initialized");
    }

    this->shaderProgram->Activate();

    this->OnApply();
}

void Effect::End()
{
    this->shaderProgram->Deactivate();
}

const EffectParameter& Effect::AddEffectParameter(const std::wstring&         name,
                                                  const EffectParameterClass& parameterClass,
                                                  const EffectParameterType&  parameterType)
{
    EffectParameter newParameter(name, parameterClass, parameterType, this->shaderProgram);
    
    this->parameters.push_back(newParameter);
    
    return this->GetEffectParameter(name);
}

const EffectParameter& Effect::GetEffectParameter(const std::wstring& name) const
{
    for (const auto& effectParameter : this->parameters)
    {
        if (effectParameter.Name() == name)
        {
            return effectParameter;
        }
    }
    
    throw std::runtime_error("Invalid parameter name");
}