// Copyright (c) Carlos Guzm�n �lvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
//---------------------------------------------------------------------------------------------------
// Partially ported from Microsoft XNA Community Game Platform Stock Effects
//---------------------------------------------------------------------------------------------------
// Microsoft XNA Community Game Platform
// Copyright (C) Microsoft Corporation. All rights reserved.
//---------------------------------------------------------------------------------------------------

#include <Graphics/SkinnedEffect.hpp>

#include <cassert>

#include <System/IO/File.hpp>
#include <Graphics/EffectHelpers.hpp>
#include <Graphics/GraphicsDevice.hpp>
#include <Graphics/Resources.hpp>
#include <Graphics/ShaderManager.hpp>

namespace SceneR
{
    namespace Graphics
    {
        using SceneR::Framework::Matrix;
        using SceneR::Framework::Vector3;

        SkinnedEffect::SkinnedEffect(GraphicsDevice& graphicsDevice)
            : Effect                     { graphicsDevice }
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
            , diffuseColorParam          { }
            , emissiveColorParam         { }
            , specularColorParam         { }
            , specularPowerParam         { }
            , eyePositionParam           { }
            , fogColorParam              { }
            , fogVectorParam             { }
            , worldParam                 { }
            , worldInverseTransposeParam { }
            , worldViewProjParam         { }
            , bonesParam                 { }
        {
            this->Name(u"SkinnedEffect");

            this->CreateShader();
            this->CacheEffectParameters();

            this->light0.Enabled(true);
        }

        SkinnedEffect::SkinnedEffect(const SkinnedEffect& effect)
            : Effect                     { effect }
            , alpha                      { effect.alpha }
            , ambientLightColor          { effect.ambientLightColor }
            , boneTransforms             { effect.boneTransforms }
            , diffuseColor               { effect.diffuseColor }
            , light0                     { effect.light0 }
            , light1                     { effect.light1 }
            , light2                     { effect.light2 }
            , lightingEnabled            { true }
            , emissiveColor              { effect.emissiveColor }
            , fogEnabled                 { effect.fogEnabled }
            , fogColor                   { effect.fogColor }
            , fogEnd                     { effect.fogEnd }
            , fogStart                   { effect.fogStart }
            , preferPerPixelLighting     { effect.preferPerPixelLighting }
            , projection                 { effect.projection }
            , specularColor              { effect.specularColor }
            , specularPower              { effect.specularPower }
            , textureEnabled             { effect.textureEnabled }
            , texture                    { effect.texture }
            , view                       { effect.view }
            , weightsPerVertex           { effect.weightsPerVertex }
            , world                      { effect.world }
            , worldView                  { effect.worldView }
            , oneLight                   { effect.oneLight }
            , shaderIndex                { effect.shaderIndex }
            , dirtyFlags                 { EffectDirtyFlags::All }
            , diffuseColorParam          { }
            , emissiveColorParam         { }
            , specularColorParam         { }
            , specularPowerParam         { }
            , eyePositionParam           { }
            , fogColorParam              { }
            , fogVectorParam             { }
            , worldParam                 { }
            , worldInverseTransposeParam { }
            , worldViewProjParam         { }
            , bonesParam                 { }
        {
            this->Name(u"SKinnedEffect");

            this->CacheEffectParameters();
        }

        SkinnedEffect::~SkinnedEffect()
        {
        }

        void SkinnedEffect::Dispose()
        {
            if (this->texture)
            {
                this->texture->Dispose();
                this->texture = nullptr;
            }

            Effect::Dispose();
        }

        float SkinnedEffect::Alpha() const
        {
            return this->alpha;
        }

        void SkinnedEffect::Alpha(const float& alpha)
        {
            if (this->alpha != alpha)
            {
                this->alpha = alpha;
                this->dirtyFlags |= EffectDirtyFlags::MaterialColor;
            }
        }

        const Vector3& SkinnedEffect::AmbientLightColor() const
        {
            return this->ambientLightColor;
        }

        void SkinnedEffect::AmbientLightColor(const Vector3& ambientLightColor)
        {
            if (this->ambientLightColor != ambientLightColor)
            {
                this->ambientLightColor = ambientLightColor;
                this->dirtyFlags |= EffectDirtyFlags::MaterialColor;
            }
        }

        const Vector3& SkinnedEffect::DiffuseColor() const
        {
            return this->diffuseColor;
        }

        void SkinnedEffect::DiffuseColor(const Vector3& diffuseColor)
        {
            if (this->diffuseColor != diffuseColor)
            {
                this->diffuseColor = diffuseColor;
                this->dirtyFlags |= EffectDirtyFlags::MaterialColor;
            }
        }

        const DirectionalLight& SkinnedEffect::DirectionalLight0() const
        {
            return this->light0;
        }

        const DirectionalLight& SkinnedEffect::DirectionalLight1() const
        {
            return this->light1;
        }

        const DirectionalLight& SkinnedEffect::DirectionalLight2() const
        {
            return this->light2;
        }

        void SkinnedEffect::EnableDefaultLighting()
        {
            this->AmbientLightColor(EffectHelpers::EnableDefaultLighting(this->light0, this->light1, this->light2));
        }

        const Vector3& SkinnedEffect::EmissiveColor() const
        {
            return this->emissiveColor;
        }

        void SkinnedEffect::EmissiveColor(const Vector3& emissiveColor)
        {
            if (this->emissiveColor != emissiveColor)
            {
                this->emissiveColor = emissiveColor;
                this->dirtyFlags |= EffectDirtyFlags::MaterialColor;
            }
        }

        const Vector3& SkinnedEffect::FogColor() const
        {
            return this->fogColor;
        }

        void SkinnedEffect::FogColor(const Vector3& fogColor)
        {
            if (this->fogColor != fogColor)
            {
                this->fogColor = fogColor;

                this->fogColorParam.SetValue(this->fogColor);
            }
        }

        bool SkinnedEffect::FogEnabled() const
        {
            return this->fogEnabled;
        }

        void SkinnedEffect::FogEnabled(const bool& fogEnabled)
        {
            if (this->fogEnabled != fogEnabled)
            {
                this->fogEnabled = fogEnabled;
                this->dirtyFlags |= EffectDirtyFlags::Fog;
            }
        }

        float SkinnedEffect::FogEnd() const
        {
            return this->fogEnd;
        }

        void SkinnedEffect::FogEnd(const float& fogEnd)
        {
            if (this->fogEnd != fogEnd)
            {
                this->fogEnd = fogEnd;
                this->dirtyFlags |= EffectDirtyFlags::Fog;
            }
        }

        float SkinnedEffect::FogStart() const
        {
            return this->fogStart;
        }

        void SkinnedEffect::FogStart(const float& fogStart)
        {
            if (this->fogStart != fogStart)
            {
                this->fogStart = fogStart;
                this->dirtyFlags |= EffectDirtyFlags::Fog;
            }
        }

        bool SkinnedEffect::LightingEnabled() const
        {
            return this->lightingEnabled;
        }

        void SkinnedEffect::LightingEnabled(const bool& lightingEnabled)
        {
            assert(false);
        }

        bool SkinnedEffect::PreferPerPixelLighting() const
        {
            return this->preferPerPixelLighting;
        }

        void SkinnedEffect::PreferPerPixelLighting(const bool& preferPerPixelLighting)
        {
            if (this->preferPerPixelLighting != preferPerPixelLighting)
            {
                this->preferPerPixelLighting = preferPerPixelLighting;
                this->dirtyFlags |= EffectDirtyFlags::ShaderIndex;
            }
        }

        const Matrix& SkinnedEffect::Projection() const
        {
            return this->projection;
        }

        void SkinnedEffect::Projection(const Matrix& projection)
        {
            this->projection = projection;
            this->dirtyFlags |= EffectDirtyFlags::WorldViewProj;
        }

        const Vector3& SkinnedEffect::SpecularColor() const
        {
            return this->specularColor;
        }

        void SkinnedEffect::SpecularColor(const Vector3& specularColor)
        {
            if (this->specularColor != specularColor)
            {
                this->specularColor = specularColor;

                this->specularColorParam.SetValue(this->specularColor);
            }
        }

        float SkinnedEffect::SpecularPower() const
        {
            return this->specularPower;
        }

        void SkinnedEffect::SpecularPower(const float& specularPower)
        {
            if (this->specularPower != specularPower)
            {
                this->specularPower = specularPower;

                this->specularPowerParam.SetValue(this->specularPower);
            }
        }

        const std::shared_ptr<Texture2D>& SkinnedEffect::Texture() const
        {
            return this->texture;
        }

        void SkinnedEffect::Texture(const std::shared_ptr<Texture2D>& texture)
        {
            if (this->texture != texture)
            {
                this->texture = texture;
                this->dirtyFlags |= EffectDirtyFlags::ShaderIndex;
            }
        }

        bool SkinnedEffect::TextureEnabled() const
        {
            return this->textureEnabled;
        }

        void SkinnedEffect::TextureEnabled(const bool& textureEnabled)
        {
            if (this->textureEnabled != textureEnabled)
            {
                this->textureEnabled = textureEnabled;
                this->dirtyFlags |= EffectDirtyFlags::ShaderIndex;
            }
        }

        const Matrix& SkinnedEffect::View() const
        {
            return this->view;
        }

        void SkinnedEffect::View(const Matrix& view)
        {
            this->view = view;
            this->dirtyFlags |= EffectDirtyFlags::WorldViewProj | EffectDirtyFlags::EyePosition | EffectDirtyFlags::Fog;
        }

        const Matrix& SkinnedEffect::World() const
        {
            return this->world;
        }

        void SkinnedEffect::World(const Matrix& world)
        {
            this->world = world;
            this->dirtyFlags |= EffectDirtyFlags::World | EffectDirtyFlags::WorldViewProj | EffectDirtyFlags::Fog;
        }

        std::vector<Matrix> SkinnedEffect::GetBoneTransforms(const std::size_t& count) const
        {
            assert(count < this->boneTransforms.size());

            std::vector<Matrix> transforms;

            transforms.reserve(count);
            transforms.assign(this->boneTransforms.begin(), this->boneTransforms.begin() + count);

            return transforms;
        }

        void SkinnedEffect::SetBoneTransforms(const std::vector<Matrix>& boneTransforms)
        {
            this->boneTransforms = boneTransforms;
            this->bonesParam.SetValue(this->boneTransforms);
        }

        std::size_t SkinnedEffect::WeightsPerVertex() const
        {
            return this->weightsPerVertex;
        }

        void SkinnedEffect::WeightsPerVertex(const std::size_t& weightsPerVertex)
        {
            assert(weightsPerVertex == 1 || weightsPerVertex == 2 || weightsPerVertex == 4);

            this->weightsPerVertex = weightsPerVertex;
            this->dirtyFlags |= EffectDirtyFlags::ShaderIndex;
        }

        void SkinnedEffect::End()
        {
            if (this->textureEnabled)
            {
                this->texture->Deactivate();
            }

            Effect::End();
        }

        void SkinnedEffect::OnApply()
        {
            this->ActivateSubroutine(ShaderType::Vertex, VSIndices[this->shaderIndex]);
            this->ActivateSubroutine(ShaderType::Fragment, PSIndices[this->shaderIndex]);

            if (this->textureEnabled)
            {
                SamplerState& sampler = this->CurrentGraphicsDevice().SamplerStates()[0];

                this->texture->Activate();

                sampler.MaxMipLevel(this->texture->LevelCount());
                sampler.OnApply(TextureTarget::Texture2D);
            }

            // Recompute the world+view+projection matrix or fog vector
            this->dirtyFlags = EffectHelpers::SetWorldViewProjAndFog(this->dirtyFlags
                                                                   , this->world
                                                                   , this->view
                                                                   , this->projection
                                                                   , this->worldView
                                                                   , this->fogEnabled
                                                                   , this->fogStart
                                                                   , this->fogEnd
                                                                   , this->worldViewProjParam
                                                                   , this->fogVectorParam);

            // Recompute the diffuse/emissive/alpha material color parameters
            if ((dirtyFlags & EffectDirtyFlags::MaterialColor) != 0)
            {
                EffectHelpers::SetMaterialColor(this->lightingEnabled
                                              , this->alpha
                                              , this->diffuseColor
                                              , this->emissiveColor
                                              , this->ambientLightColor
                                              , this->diffuseColorParam
                                              , this->emissiveColorParam);

                this->dirtyFlags &= ~EffectDirtyFlags::MaterialColor;
            }

            if (this->lightingEnabled)
            {
                // Recompute the world inverse transpose and eye position
                this->dirtyFlags = EffectHelpers::SetLightingMatrices(this->dirtyFlags
                                                                    , this->world
                                                                    , this->view
                                                                    , this->worldParam
                                                                    , this->worldInverseTransposeParam
                                                                    , this->eyePositionParam);

                // Check if we can use the only-bother-with-the-first-light shader optimization.
                bool newOneLight = !this->light1.Enabled() && !this->light2.Enabled();

                if (this->oneLight != newOneLight)
                {
                    this->oneLight    = newOneLight;
                    this->dirtyFlags |= EffectDirtyFlags::ShaderIndex;
                }
                else
                {
                    if (this->light0.Enabled())
                    {
                        this->parameters[u"DirLight0Direction"].SetValue(this->light0.Direction());
                        this->parameters[u"DirLight0DiffuseColor"].SetValue(this->light0.DiffuseColor());
                        this->parameters[u"DirLight0SpecularColor"].SetValue(this->light0.SpecularColor());
                    }

                    if (this->light1.Enabled())
                    {
                        this->parameters[u"DirLight1Direction"].SetValue(this->light1.Direction());
                        this->parameters[u"DirLight1DiffuseColor"].SetValue(this->light1.DiffuseColor());
                        this->parameters[u"DirLight1SpecularColor"].SetValue(this->light1.SpecularColor());
                    }

                    if (this->light2.Enabled())
                    {
                        this->parameters[u"DirLight2Direction"].SetValue(this->light2.Direction());
                        this->parameters[u"DirLight2DiffuseColor"].SetValue(this->light2.DiffuseColor());
                        this->parameters[u"DirLight2SpecularColor"].SetValue(this->light2.SpecularColor());
                    }
                }
            }

            // Recompute the shader index
            if ((this->dirtyFlags & EffectDirtyFlags::ShaderIndex) != 0)
            {
                this->shaderIndex = 0;

                if (!this->fogEnabled)
                {
                    this->shaderIndex += 1;
                }

                if (this->weightsPerVertex == 2)
                {
                    this->shaderIndex += 2;
                }
                else if (weightsPerVertex == 4)
                {
                    this->shaderIndex += 4;
                }

                if (this->preferPerPixelLighting)
                {
                    this->shaderIndex += 12;
                }
                else if (this->oneLight)
                {
                    this->shaderIndex += 6;
                }

                this->dirtyFlags &= ~EffectDirtyFlags::ShaderIndex;
            }
        }

        void SkinnedEffect::CreateShader()
        {
            const auto& includes = std::vector<std::string> { ShaderManager::SkinnedEffectIncludePath
                                                            , ShaderManager::StructuresIncludePath
                                                            , ShaderManager::CommonIncludePath
                                                            , ShaderManager::LightingIncludePath };

            this->AddShader(u"VSSkinnedEffect", ShaderType::Vertex, Resources::SkinnedEffect_vertString, includes);
            this->AddShader(u"FSSkinnedEffect", ShaderType::Fragment, Resources::SkinnedEffect_fragString, includes);
            this->Build();
        }

        void SkinnedEffect::CacheEffectParameters()
        {
            this->diffuseColorParam          = this->parameters[u"DiffuseColor"];
            this->emissiveColorParam         = this->parameters[u"EmissiveColor"];
            this->specularColorParam         = this->parameters[u"SpecularColor"];
            this->specularPowerParam         = this->parameters[u"SpecularPower"];
            this->fogColorParam              = this->parameters[u"FogColor"];
            this->fogVectorParam             = this->parameters[u"FogVector"];
            this->eyePositionParam           = this->parameters[u"EyePosition"];
            this->worldParam                 = this->parameters[u"World"];
            this->worldViewProjParam         = this->parameters[u"WorldViewProj"];
            this->worldInverseTransposeParam = this->parameters[u"WorldInverseTranspose"];
            this->bonesParam                 = this->parameters[u"Bones[0]"];

            /*
            this->light0 = light { this->parameters[u"DirLight0Direction"].GetValueVector3()
                                            , this->parameters[u"DirLight0DiffuseColor"].GetValueVector3()
                                            , this->parameters[u"DirLight0SpecularColor"].GetValueVector3() };

            this->light1 = light { this->parameters[u"DirLight1Direction"].GetValueVector3()
                                            , this->parameters[u"DirLight1DiffuseColor"].GetValueVector3()
                                            , this->parameters[u"DirLight1SpecularColor"].GetValueVector3() };

            this->light2 = light { this->parameters[u"DirLight2Direction"].GetValueVector3()
                                            , this->parameters[u"DirLight2DiffuseColor"].GetValueVector3()
                                            , this->parameters[u"DirLight2SpecularColor"].GetValueVector3() };
            */
        }

        std::uint32_t SkinnedEffect::VSIndices[18] =
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

        std::uint32_t SkinnedEffect::PSIndices[18] =
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
