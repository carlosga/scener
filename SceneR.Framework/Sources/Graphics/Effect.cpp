// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/Effect.hpp>

#include <cassert>

#include <Graphics/EffectDirtyFlags.hpp>
#include <Graphics/EffectHelpers.hpp>
#include <Graphics/GraphicsDevice.hpp>
#include <Graphics/Shader.hpp>
#include <Graphics/UniformBufferObject.hpp>
#include <System/Math.hpp>

namespace SceneR
{
    namespace Graphics
    {
        using System::Math;
        using SceneR::Framework::Matrix;
        using SceneR::Framework::Vector3;

        Effect::Effect(GraphicsDevice& graphicsDevice)
            : GraphicsResource           { graphicsDevice }
            , alpha                      { 1.0 }
            , ambientLightColor          { Vector3::Zero }
            , boneTransforms             ( 0 )
            , diffuseColor               { Vector3::One }
            , light0                     { }
            , light1                     { }
            , light2                     { }
            , lightingEnabled            { true }
            , emissiveColor              { Vector3::Zero }
            , fogEnabled                 { false }
            , fogColor                   { Vector3::Zero }
            , fogEnd                     { 1.0f }
            , fogStart                   { 0.0f }
            , preferPerPixelLighting     { false }
            , projection                 { Matrix::Identity }
            , specularColor              { Vector3::One }
            , specularPower              { 16.0f }
            , textureEnabled             { false }
            , texture                    { nullptr }
            , view                       { Matrix::Identity }
            , weightsPerVertex           { 2 }
            , world                      { Matrix::Identity }
            , worldView                  { Matrix::Identity }
            , oneLight                   { false }
            , shaderIndex                { 0 }
            , dirtyFlags                 { EffectDirtyFlags::All }
            , passes                     { }
            , parameters                 { }
        {
            // this->Name(u"Effect");

            // this->CreateShader();
            // this->CacheEffectParameters();

            // this->light0.Enabled(true);
        }

        Effect::~Effect()
        {
        }

        void Effect::dispose()
        {
            if (this->id != 0)
            {
                if (this->texture)
                {
                    this->texture = nullptr;
                }

                // Clear parameter collection
                // this->parameters.Clear();

                // Dipose all the shader instances
                if (this->shaders.size() > 0)
                {
                    for (auto& shader : this->shaders)
                    {
                        shader->dispose();
                    }

                    this->shaders.clear();
                }

                // dispose the uniform buffer object
                this->uniformBuffer->dispose();
                this->uniformBuffer = nullptr;

                // Delete the shader program
                glDeleteProgram(this->id);

                // Reset the shader program name
                this->id = 0;
            }
        }

        float Effect::Alpha() const
        {
            return this->alpha;
        }

        void Effect::Alpha(const float& alpha)
        {
            if (Math::Equal(this->alpha, alpha))
            {
                this->alpha = alpha;
                this->dirtyFlags |= EffectDirtyFlags::MaterialColor;
            }
        }

        const Vector3& Effect::AmbientLightColor() const
        {
            return this->ambientLightColor;
        }

        void Effect::AmbientLightColor(const Vector3& ambientLightColor)
        {
            if (this->ambientLightColor != ambientLightColor)
            {
                this->ambientLightColor = ambientLightColor;
                this->dirtyFlags |= EffectDirtyFlags::MaterialColor;
            }
        }

        const Vector3& Effect::DiffuseColor() const
        {
            return this->diffuseColor;
        }

        void Effect::DiffuseColor(const Vector3& diffuseColor)
        {
            if (this->diffuseColor != diffuseColor)
            {
                this->diffuseColor = diffuseColor;
                this->dirtyFlags |= EffectDirtyFlags::MaterialColor;
            }
        }

        const DirectionalLight& Effect::DirectionalLight0() const
        {
            return this->light0;
        }

        const DirectionalLight& Effect::DirectionalLight1() const
        {
            return this->light1;
        }

        const DirectionalLight& Effect::DirectionalLight2() const
        {
            return this->light2;
        }

        void Effect::EnableDefaultLighting()
        {
            this->AmbientLightColor(EffectHelpers::EnableDefaultLighting(this->light0, this->light1, this->light2));
        }

        const Vector3& Effect::EmissiveColor() const
        {
            return this->emissiveColor;
        }

        void Effect::EmissiveColor(const Vector3& emissiveColor)
        {
            if (this->emissiveColor != emissiveColor)
            {
                this->emissiveColor = emissiveColor;
                this->dirtyFlags |= EffectDirtyFlags::MaterialColor;
            }
        }

        const Vector3& Effect::FogColor() const
        {
            return this->fogColor;
        }

        void Effect::FogColor(const Vector3& fogColor)
        {
//            if (this->fogColor != fogColor)
//            {
//                this->fogColor = fogColor;
//
//                this->fogColorParam.SetValue(this->fogColor);
//            }
        }

        bool Effect::FogEnabled() const
        {
            return this->fogEnabled;
        }

        void Effect::FogEnabled(const bool& fogEnabled)
        {
            if (this->fogEnabled != fogEnabled)
            {
                this->fogEnabled = fogEnabled;
                this->dirtyFlags |= EffectDirtyFlags::Fog;
            }
        }

        float Effect::FogEnd() const
        {
            return this->fogEnd;
        }

        void Effect::FogEnd(const float& fogEnd)
        {
            if (!Math::Equal(this->fogEnd, fogEnd))
            {
                this->fogEnd = fogEnd;
                this->dirtyFlags |= EffectDirtyFlags::Fog;
            }
        }

        float Effect::FogStart() const
        {
            return this->fogStart;
        }

        void Effect::FogStart(const float& fogStart)
        {
            if (!Math::Equal(this->fogStart, fogStart))
            {
                this->fogStart = fogStart;
                this->dirtyFlags |= EffectDirtyFlags::Fog;
            }
        }

        bool Effect::LightingEnabled() const
        {
            return this->lightingEnabled;
        }

        void Effect::LightingEnabled(const bool& lightingEnabled)
        {
            assert(false);
        }

        bool Effect::PreferPerPixelLighting() const
        {
            return this->preferPerPixelLighting;
        }

        void Effect::PreferPerPixelLighting(const bool& preferPerPixelLighting)
        {
            if (this->preferPerPixelLighting != preferPerPixelLighting)
            {
                this->preferPerPixelLighting = preferPerPixelLighting;
                this->dirtyFlags |= EffectDirtyFlags::ShaderIndex;
            }
        }

        const Matrix& Effect::Projection() const
        {
            return this->projection;
        }

        void Effect::Projection(const Matrix& projection)
        {
            this->projection = projection;
            this->dirtyFlags |= EffectDirtyFlags::WorldViewProj;
        }

        const Vector3& Effect::SpecularColor() const
        {
            return this->specularColor;
        }

        void Effect::SpecularColor(const Vector3& specularColor)
        {
//            if (this->specularColor != specularColor)
//            {
//                this->specularColor = specularColor;
//
//                this->specularColorParam.SetValue(this->specularColor);
//            }
        }

        float Effect::SpecularPower() const
        {
            return this->specularPower;
        }

        void Effect::SpecularPower(const float& specularPower)
        {
//            if (!Math::Equal(this->specularPower, specularPower))
//            {
//                this->specularPower = specularPower;
//
//                this->specularPowerParam.SetValue(this->specularPower);
//            }
        }

        const std::shared_ptr<Texture2D>& Effect::Texture() const
        {
            return this->texture;
        }

        void Effect::Texture(const std::shared_ptr<Texture2D>& texture)
        {
            if (this->texture != texture)
            {
                this->texture = texture;
                this->dirtyFlags |= EffectDirtyFlags::ShaderIndex;
            }
        }

        bool Effect::TextureEnabled() const
        {
            return this->textureEnabled;
        }

        void Effect::TextureEnabled(const bool& textureEnabled)
        {
            if (this->textureEnabled != textureEnabled)
            {
                this->textureEnabled = textureEnabled;
                this->dirtyFlags |= EffectDirtyFlags::ShaderIndex;
            }
        }

        const Matrix& Effect::View() const
        {
            return this->view;
        }

        void Effect::View(const Matrix& view)
        {
            this->view = view;
            this->dirtyFlags |= EffectDirtyFlags::WorldViewProj | EffectDirtyFlags::EyePosition | EffectDirtyFlags::Fog;
        }

        const Matrix& Effect::World() const
        {
            return this->world;
        }

        void Effect::World(const Matrix& world)
        {
            this->world = world;
            this->dirtyFlags |= EffectDirtyFlags::World | EffectDirtyFlags::WorldViewProj | EffectDirtyFlags::Fog;
        }

        std::vector<Matrix> Effect::GetBoneTransforms(const std::size_t& count) const
        {
            assert(count < this->boneTransforms.size());

            std::vector<Matrix> transforms;

            transforms.reserve(count);
            transforms.assign(this->boneTransforms.begin(), this->boneTransforms.begin() + count);

            return transforms;
        }

        void Effect::SetBoneTransforms(const std::vector<Matrix>& boneTransforms)
        {
//            this->boneTransforms = boneTransforms;
//            this->bonesParam.SetValue(this->boneTransforms);
        }

        std::size_t Effect::WeightsPerVertex() const
        {
            return this->weightsPerVertex;
        }

        void Effect::WeightsPerVertex(const std::size_t& weightsPerVertex)
        {
            assert(weightsPerVertex == 1 || weightsPerVertex == 2 || weightsPerVertex == 4);

            this->weightsPerVertex = weightsPerVertex;
            this->dirtyFlags |= EffectDirtyFlags::ShaderIndex;
        }

        void Effect::OnApply()
        {
//            this->ActivateSubroutine(ShaderType::Vertex, VSIndices[this->shaderIndex]);
//            this->ActivateSubroutine(ShaderType::Fragment, PSIndices[this->shaderIndex]);
//
//            if (this->textureEnabled)
//            {
//                SamplerState& sampler = this->graphics_device().SamplerStates()[0];
//
//                sampler.MaxMipLevel(this->texture->LevelCount());
//                sampler.OnApply(this->texture->Id());
//
//                this->texture->Activate();
//            }
//
//            // Recompute the world+view+projection matrix or fog vector
//            this->dirtyFlags = EffectHelpers::SetWorldViewProjAndFog(this->dirtyFlags
//                , this->world
//                , this->view
//                , this->projection
//                , this->worldView
//                , this->fogEnabled
//                , this->fogStart
//                , this->fogEnd
//                , this->worldViewProjParam
//                , this->fogVectorParam);
//
//            // Recompute the diffuse/emissive/alpha material color parameters
//            if ((dirtyFlags & EffectDirtyFlags::MaterialColor) != 0)
//            {
//                EffectHelpers::SetMaterialColor(this->lightingEnabled
//                    , this->alpha
//                    , this->diffuseColor
//                    , this->emissiveColor
//                    , this->ambientLightColor
//                    , this->diffuseColorParam
//                    , this->emissiveColorParam);
//
//                this->dirtyFlags &= ~EffectDirtyFlags::MaterialColor;
//            }
//
//            if (this->lightingEnabled)
//            {
//                // Recompute the world inverse transpose and eye position
//                this->dirtyFlags = EffectHelpers::SetLightingMatrices(this->dirtyFlags
//                    , this->world
//                    , this->view
//                    , this->worldParam
//                    , this->worldInverseTransposeParam
//                    , this->eyePositionParam);
//
//                // Check if we can use the only-bother-with-the-first-light shader optimization.
//                bool newOneLight = !this->light1.Enabled() && !this->light2.Enabled();
//
//                if (this->oneLight != newOneLight)
//                {
//                    this->oneLight    = newOneLight;
//                    this->dirtyFlags |= EffectDirtyFlags::ShaderIndex;
//                }
//                else
//                {
//                    if (this->light0.Enabled())
//                    {
//                        this->parameters[u"DirLight0Direction"].SetValue(this->light0.Direction());
//                        this->parameters[u"DirLight0DiffuseColor"].SetValue(this->light0.DiffuseColor());
//                        this->parameters[u"DirLight0SpecularColor"].SetValue(this->light0.SpecularColor());
//                    }
//
//                    if (this->light1.Enabled())
//                    {
//                        this->parameters[u"DirLight1Direction"].SetValue(this->light1.Direction());
//                        this->parameters[u"DirLight1DiffuseColor"].SetValue(this->light1.DiffuseColor());
//                        this->parameters[u"DirLight1SpecularColor"].SetValue(this->light1.SpecularColor());
//                    }
//
//                    if (this->light2.Enabled())
//                    {
//                        this->parameters[u"DirLight2Direction"].SetValue(this->light2.Direction());
//                        this->parameters[u"DirLight2DiffuseColor"].SetValue(this->light2.DiffuseColor());
//                        this->parameters[u"DirLight2SpecularColor"].SetValue(this->light2.SpecularColor());
//                    }
//                }
//            }
//
//            // Recompute the shader index
//            if ((this->dirtyFlags & EffectDirtyFlags::ShaderIndex) != 0)
//            {
//                this->shaderIndex = 0;
//
//                if (!this->fogEnabled)
//                {
//                    this->shaderIndex += 1;
//                }
//
//                if (this->weightsPerVertex == 2)
//                {
//                    this->shaderIndex += 2;
//                }
//                else if (weightsPerVertex == 4)
//                {
//                    this->shaderIndex += 4;
//                }
//
//                if (this->preferPerPixelLighting)
//                {
//                    this->shaderIndex += 12;
//                }
//                else if (this->oneLight)
//                {
//                    this->shaderIndex += 6;
//                }
//
//                this->dirtyFlags &= ~EffectDirtyFlags::ShaderIndex;
//            }
        }

        void Effect::CreateShader()
        {
//            const auto& includes = std::vector<std::string> { ShaderManager::EffectIncludePath
//                , ShaderManager::StructuresIncludePath
//                , ShaderManager::CommonIncludePath
//                , ShaderManager::LightingIncludePath };
//
//            this->AddShader(u"VSEffect", ShaderType::Vertex, Resources::Effect_vert, includes);
//            this->AddShader(u"FSEffect", ShaderType::Fragment, Resources::Effect_frag, includes);
//            this->Build();
        }

        void Effect::CacheEffectParameters()
        {
//            this->diffuseColorParam          = this->parameters[u"DiffuseColor"];
//            this->emissiveColorParam         = this->parameters[u"EmissiveColor"];
//            this->specularColorParam         = this->parameters[u"SpecularColor"];
//            this->specularPowerParam         = this->parameters[u"SpecularPower"];
//            this->fogColorParam              = this->parameters[u"FogColor"];
//            this->fogVectorParam             = this->parameters[u"FogVector"];
//            this->eyePositionParam           = this->parameters[u"EyePosition"];
//            this->worldParam                 = this->parameters[u"World"];
//            this->worldViewProjParam         = this->parameters[u"WorldViewProj"];
//            this->worldInverseTransposeParam = this->parameters[u"WorldInverseTranspose"];
//            this->bonesParam                 = this->parameters[u"Bones[0]"];
        }

        void Effect::Begin()
        {
//            glUseProgram(this->id);
//            this->uniformBuffer->Activate();
//
//            this->OnApply();
        }

        void Effect::End()
        {
//            if (this->textureEnabled)
//            {
//                this->texture->Deactivate();
//            }
//
//            this->uniformBuffer->Deactivate();
//
//            glUseProgram(0);
        }

        void Effect::AddShader(const std::u16string&            name
                             , const ShaderType&                type
                             , const std::vector<std::uint8_t>& source)
        {
//            this->AddShader(name, type, source, std::vector<std::string>());
        }

        void Effect::AddShader(const std::u16string&            name
                             , const ShaderType&                type
                             , const std::vector<std::uint8_t>& source
                             , const std::vector<std::string>&  includes)
        {
//            this->shaders.push_back(std::make_shared<Shader>(name, type, source, includes));
        }

        void Effect::Build()
        {
//            // Compile the shaders ...
//            for (auto& s : this->shaders)
//            {
//                s->Compile();
//            }
//
//            // ... Create the program object
//            this->id = glCreateProgram();
//
//            if (this->id == 0)
//            {
//                throw std::runtime_error("glCreateProgram failed");
//            }
//
//            // ... attach the shaders to the new shader program
//            for (const auto& s : this->shaders)
//            {
//                // Attach the shader
//                glAttachShader(this->id, s->id);
//            }
//
//            // ... link the shader program
//            glLinkProgram(this->id);
//
//            // ... verify program linking
//            this->VerifyLinkingState();
//
//            // ... fill uniform buffer info
//            this->uniformBuffer = std::make_shared<UniformBufferObject>(u"ConstantBuffer", this->id);
//            this->uniformBuffer->Describe();
//
//            // ... describe efffect parameters
//            this->DescribeParameters();
        }

        void Effect::ActivateSubroutine(const std::uint32_t& subroutineIndex) const
        {
//            for (const auto& shader : this->shaders)
//            {
//                this->ActivateSubroutine(shader->Type(), subroutineIndex);
//            }
        }

        void Effect::ActivateSubroutine(const ShaderType& type, const std::uint32_t& subroutineIndex) const
        {
//            glUniformSubroutinesuiv(static_cast<GLenum>(type), 1, &subroutineIndex);
        }

        void Effect::VerifyLinkingState()
        {
//            // ... verify program linking
//            GLint status;
//            glGetProgramiv(this->id, GL_LINK_STATUS, &status);
//
//            if (status == GL_FALSE)
//            {
//                auto msg = std::string("Program linking failure: ");
//
//                GLint infoLogLength;
//                glGetProgramiv(this->id, GL_INFO_LOG_LENGTH, &infoLogLength);
//
//                if (infoLogLength)
//                {
//                    std::string linkErrorMessage("", static_cast<std::size_t>(infoLogLength));
//
//                    glGetProgramInfoLog(this->id, infoLogLength, NULL, &linkErrorMessage[0]);
//
//                    msg += linkErrorMessage;
//                }
//
//                //this->dispose();
//
//                throw std::runtime_error(msg);
//            }
        }

        void Effect::DescribeParameters()
        {
//            // Check the number of active uniforms
//            std::int32_t activeUniforms = 0;
//
//            glGetActiveUniformBlockiv(this->id, this->uniformBuffer->Index(), GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS, &activeUniforms);
//
//            std::vector<std::int32_t> indices(activeUniforms, 0);
//            std::vector<std::int32_t> nameLengths(activeUniforms, 0);
//            std::vector<std::int32_t> offsets(activeUniforms, 0);
//            std::vector<std::int32_t> types(activeUniforms, 0);
//
//            glGetActiveUniformBlockiv(this->id, this->uniformBuffer->Index(), GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES, indices.data());
//
//            GLuint* address = reinterpret_cast<GLuint*>(indices.data());
//
//            glGetActiveUniformsiv(this->id, activeUniforms, address, GL_UNIFORM_NAME_LENGTH, nameLengths.data());
//            glGetActiveUniformsiv(this->id, activeUniforms, address, GL_UNIFORM_OFFSET     , offsets.data());
//            glGetActiveUniformsiv(this->id, activeUniforms, address, GL_UNIFORM_TYPE       , types.data());
//
//            for (std::int32_t i = 0; i < activeUniforms; i++)
//            {
//                GLsizei length = 0;
//                GLint   size   = 0;
//                GLenum  type   = GL_ZERO;
//                auto    name   = std::vector<char>(nameLengths[i], 0);
//
//                glGetActiveUniform(this->id, indices[i], nameLengths[i], &length, &size, &type, name.data());
//
//                this->parameters.Add({ name.begin(), name.begin() + length }
//                                   , static_cast<std::uint32_t>(indices[i])
//                                   , static_cast<std::uint32_t>(offsets[i])
//                                   , static_cast<std::uint32_t>(types[i])
//                                   , this->uniformBuffer);
//            }
        }

        std::uint32_t Effect::VSIndices[18] =
        {
            0,      // vertex lighting, one bone
            0,      // vertex lighting, one bone, no fog
            1,      // vertex lighting, two bones
            1,      // vertex lighting, two bones, no fog
            2,      // vertex lighting, four bones
            2,      // vertex lighting, four bones, no fog

            3,      // one light, one bone
            3,      // one light, one bone, no fog
            4,      // one light, two bones
            4,      // one light, two bones, no fog
            5,      // one light, four bones
            5,      // one light, four bones, no fog

            6,      // pixel lighting, one bone
            6,      // pixel lighting, one bone, no fog
            7,      // pixel lighting, two bones
            7,      // pixel lighting, two bones, no fog
            8,      // pixel lighting, four bones
            8,      // pixel lighting, four bones, no fog
        };

        std::uint32_t Effect::PSIndices[18] =
        {
            0,      // vertex lighting, one bone
            1,      // vertex lighting, one bone, no fog
            0,      // vertex lighting, two bones
            1,      // vertex lighting, two bones, no fog
            0,      // vertex lighting, four bones
            1,      // vertex lighting, four bones, no fog

            0,      // one light, one bone
            1,      // one light, one bone, no fog
            0,      // one light, two bones
            1,      // one light, two bones, no fog
            0,      // one light, four bones
            1,      // one light, four bones, no fog

            2,      // pixel lighting, one bone
            2,      // pixel lighting, one bone, no fog
            2,      // pixel lighting, two bones
            2,      // pixel lighting, two bones, no fog
            2,      // pixel lighting, four bones
            2,      // pixel lighting, four bones, no fog
        };
    }
}
