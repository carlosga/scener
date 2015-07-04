// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/Effect.hpp>

#include <cassert>

#include <Framework/Matrix.hpp>
#include <Framework/Quaternion.hpp>
#include <Framework/Vector2.hpp>
#include <Framework/Vector3.hpp>
#include <Framework/Vector4.hpp>
#include <Graphics/Shader.hpp>
#include <Graphics/UniformBufferObject.hpp>

using namespace System;
using namespace SceneR::Graphics;

Effect::Effect(GraphicsDevice& graphicsDevice)
    : GraphicsResource { graphicsDevice }
    , parameters    { }
    , id            { 0 }
    , shaders       ( 0 )
    , uniformBuffer ( nullptr )
{
}

Effect::Effect(const Effect& effect)
    : GraphicsResource { effect.graphicsDevice }
    , parameters       { effect.parameters }
    , id               { effect.id }
    , shaders          ( effect.shaders )
    , uniformBuffer    { effect.uniformBuffer }
{
}

Effect::~Effect()
{
}

void Effect::Dispose()
{
    if (this->id != 0)
    {
        // Clear parameter collection
        this->parameters.Clear();

        // Dipose all the shader instances
        if (this->shaders.size() > 0)
        {
            for (auto& shader : this->shaders)
            {
                shader->Dispose();
            }

            this->shaders.clear();
        }

        // Dispose the uniform buffer object
        this->uniformBuffer->Dispose();
        this->uniformBuffer = nullptr;

        // Delete the shader program
        glDeleteProgram(this->id);

        // Reset the shader program name
        this->id = 0;
    }
}

EffectParameterCollection& Effect::Parameters()
{
    return this->parameters;
}

void Effect::Begin()
{
    glUseProgram(this->id);
    this->uniformBuffer->Activate();

    this->OnApply();
}

void Effect::End()
{
    this->uniformBuffer->Deactivate();
    glUseProgram(0);
}

void Effect::AddShader(const std::u16string& name, const ShaderType& type, const std::string& source)
{
    this->AddShader(name, type, source, std::vector<std::string>());
}

void Effect::AddShader(const std::u16string&           name
                     , const ShaderType&               type
                     , const std::string&              source
                     , const std::vector<std::string>& includes)
{
    this->shaders.push_back(std::make_shared<Shader>(name, type, source, includes));
}

void Effect::Build()
{
    // Compile the shaders ...
    for (auto &s : this->shaders)
    {
        s->Compile();
    }

    // ... Create the program object
    this->id = glCreateProgram();

    if (this->id == 0)
    {
        throw std::runtime_error("glCreateProgram failed");
    }

    // ... attach the shaders to the new shader program
    for (auto &s : this->shaders)
    {
        // Attach the shader
        glAttachShader(this->id, s->id);
    }

    // ... link the shader program
    glLinkProgram(this->id);

    // ... verify program linking
    this->VerifyLinkingState();

    // ... fill uniform buffer info
    this->uniformBuffer = std::make_shared<UniformBufferObject>(u"ConstantBuffer", this->id);
    this->uniformBuffer->Describe();

    // ... describe efffect parameters
    this->DescribeParameters();
}

void Effect::ActivateSubroutine(const uint32_t& subroutineIndex) const
{
    for (const auto& shader : this->shaders)
    {
        this->ActivateSubroutine(shader->Type(), subroutineIndex);
    }
}

void Effect::ActivateSubroutine(const ShaderType& type, const uint32_t& subroutineIndex) const
{
    glUniformSubroutinesuiv(static_cast<GLenum>(type), 1, &subroutineIndex);
}

void Effect::VerifyLinkingState()
{
    // ... verify program linking
    GLint status;
    glGetProgramiv(this->id, GL_LINK_STATUS, &status);

    if (status == GL_FALSE)
    {
        auto msg = std::string("Program linking failure: ");

        GLint infoLogLength;
        glGetProgramiv(this->id, GL_INFO_LOG_LENGTH, &infoLogLength);

        if (infoLogLength)
        {
            std::string linkErrorMessage("", static_cast<Size>(infoLogLength));

            glGetProgramInfoLog(this->id, infoLogLength, NULL, &linkErrorMessage[0]);

            msg += linkErrorMessage;
        }

        //this->Dispose();

        throw std::runtime_error(msg);
    }
}

void Effect::DescribeParameters()
{
    // Check the number of active uniforms
    int32_t activeUniforms = 0;

    glGetActiveUniformBlockiv(this->id, this->uniformBuffer->Index(), GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS, &activeUniforms);

    std::vector<int32_t> indices(activeUniforms, 0);
    std::vector<int32_t> nameLengths(activeUniforms, 0);
    std::vector<int32_t> offsets(activeUniforms, 0);
    std::vector<int32_t> types(activeUniforms, 0);

    glGetActiveUniformBlockiv(this->id, this->uniformBuffer->Index(), GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES, indices.data());

    GLuint* address = reinterpret_cast<GLuint*>(indices.data());

    glGetActiveUniformsiv(this->id, activeUniforms, address, GL_UNIFORM_NAME_LENGTH, nameLengths.data());
    glGetActiveUniformsiv(this->id, activeUniforms, address, GL_UNIFORM_OFFSET     , offsets.data());
    glGetActiveUniformsiv(this->id, activeUniforms, address, GL_UNIFORM_TYPE       , types.data());

    for (int32_t i = 0; i < activeUniforms; i++)
    {
        GLsizei length = 0;
        GLint   size   = 0;
        GLenum  type   = GL_ZERO;
        auto    name   = std::vector<char>(nameLengths[i], 0);

        glGetActiveUniform(this->id, indices[i], nameLengths[i], &length, &size, &type, name.data());

        this->parameters.Add({ name.begin(), name.begin() + length }
                           , static_cast<uint32_t>(indices[i])
                           , static_cast<uint32_t>(offsets[i])
                           , static_cast<uint32_t>(types[i])
                           , this->uniformBuffer);
    }
}
