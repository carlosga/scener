// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
//---------------------------------------------------------------------------------------------------
// Partially ported from Microsoft XNA Community Game Platform Stock Effects
//---------------------------------------------------------------------------------------------------
// Microsoft XNA Community Game Platform
// Copyright (C) Microsoft Corporation. All rights reserved.
//---------------------------------------------------------------------------------------------------

#include <Graphics/BasicEffect.hpp>

#include <System/IO/File.hpp>
#include <System/Math.hpp>
#include <Framework/Vector4.hpp>
#include <Graphics/EffectHelpers.hpp>
#include <Graphics/GraphicsDevice.hpp>
#include <Graphics/ShaderManager.hpp>
#include <Graphics/Resources.hpp>

namespace SceneR
{
    namespace Graphics
    {
        using System::Math;
        using SceneR::Framework::Matrix;
        using SceneR::Framework::Vector3;

        BasicEffect::BasicEffect(GraphicsDevice& graphicsDevice)
            : Effect                     { graphicsDevice }
            , alpha                      { 1.0f }
            , ambientLightColor          { Vector3::Zero }
            , diffuseColor               { Vector3::One }
            , light0                     { }
            , light1                     { }
            , light2                     { }
            , lightingEnabled            { false }
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
            , vertexColorEnabled         { false }
            , view                       { Matrix::Identity }
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
        {
            this->Name(u"BasicEffect");

            this->CreateShader();
            this->CacheEffectParameters();

            this->light0.Enabled(true);
        }

        BasicEffect::BasicEffect(const BasicEffect& effect)
            : Effect                     { effect }
            , alpha                      { effect.alpha }
            , ambientLightColor          { effect.ambientLightColor }
            , diffuseColor               { effect.diffuseColor }
            , light0                     { effect.light0 }
            , light1                     { effect.light1 }
            , light2                     { effect.light2 }
            , lightingEnabled            { effect.lightingEnabled }
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
            , vertexColorEnabled         { effect.vertexColorEnabled }
            , view                       { effect.view }
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
        {
            this->Name(u"BasicEffect");

            this->CacheEffectParameters();
        }

        BasicEffect::~BasicEffect()
        {
        }

        void BasicEffect::Dispose()
        {
            if (this->texture)
            {
                this->texture->Dispose();
                this->texture = nullptr;
            }

            Effect::Dispose();
        }

        float BasicEffect::Alpha() const
        {
            return this->alpha;
        }

        void BasicEffect::Alpha(const float& alpha)
        {
            if (!Math::Equal(this->alpha, alpha))
            {
                this->alpha = alpha;
                this->dirtyFlags |= EffectDirtyFlags::MaterialColor;
            }
        }

        const Vector3& BasicEffect::AmbientLightColor() const
        {
            return this->ambientLightColor;
        }

        void BasicEffect::AmbientLightColor(const Vector3& ambientLightColor)
        {
            if (this->ambientLightColor != ambientLightColor)
            {
                this->ambientLightColor = ambientLightColor;
                this->dirtyFlags |= EffectDirtyFlags::MaterialColor;
            }
        }

        const Vector3& BasicEffect::DiffuseColor() const
        {
            return this->diffuseColor;
        }

        void BasicEffect::DiffuseColor(const Vector3& diffuseColor)
        {
            if (this->diffuseColor != diffuseColor)
            {
                this->diffuseColor = diffuseColor;
                this->dirtyFlags |= EffectDirtyFlags::MaterialColor;
            }
        }

        const DirectionalLight& BasicEffect::DirectionalLight0() const
        {
            return this->light0;
        }

        const DirectionalLight& BasicEffect::DirectionalLight1() const
        {
            return this->light1;
        }

        const DirectionalLight& BasicEffect::DirectionalLight2() const
        {
            return this->light2;
        }

        void BasicEffect::EnableDefaultLighting()
        {
            this->LightingEnabled(true);

            this->AmbientLightColor(EffectHelpers::EnableDefaultLighting(this->light0, this->light1, this->light2));
        }

        const Vector3& BasicEffect::EmissiveColor() const
        {
            return this->emissiveColor;
        }

        void BasicEffect::EmissiveColor(const Vector3& emissiveColor)
        {
            if (this->emissiveColor != emissiveColor)
            {
                this->emissiveColor = emissiveColor;
                this->dirtyFlags |= EffectDirtyFlags::MaterialColor;
            }
        }

        const Vector3& BasicEffect::FogColor() const
        {
            return this->fogColor;
        }

        void BasicEffect::FogColor(const Vector3& fogColor)
        {
            if (this->fogColor != fogColor)
            {
                this->fogColor = fogColor;

                this->fogColorParam.SetValue(this->fogColor);
            }
        }

        bool BasicEffect::FogEnabled() const
        {
            return this->fogEnabled;
        }

        void BasicEffect::FogEnabled(const bool& fogEnabled)
        {
            if (this->fogEnabled != fogEnabled)
            {
                this->fogEnabled = fogEnabled;
                this->dirtyFlags |= EffectDirtyFlags::Fog;
            }
        }

        float BasicEffect::FogEnd() const
        {
            return this->fogEnd;
        }

        void BasicEffect::FogEnd(const float& fogEnd)
        {
            if (!Math::Equal(this->fogEnd, fogEnd))
            {
                this->fogEnd = fogEnd;
                this->dirtyFlags |= EffectDirtyFlags::Fog;
            }
        }

        float BasicEffect::FogStart() const
        {
            return this->fogStart;
        }

        void BasicEffect::FogStart(const float& fogStart)
        {
            if (!Math::Equal(this->fogStart, fogStart))
            {
                this->fogStart = fogStart;
                this->dirtyFlags |= EffectDirtyFlags::Fog;
            }
        }

        bool BasicEffect::LightingEnabled() const
        {
            return this->lightingEnabled;
        }

        void BasicEffect::LightingEnabled(const bool& lightingEnabled)
        {
            if (this->lightingEnabled != lightingEnabled)
            {
                this->lightingEnabled = lightingEnabled;
                this->dirtyFlags |= EffectDirtyFlags::ShaderIndex | EffectDirtyFlags::MaterialColor;
            }
        }

        bool BasicEffect::PreferPerPixelLighting() const
        {
            return this->preferPerPixelLighting;
        }

        void BasicEffect::PreferPerPixelLighting(const bool& preferPerPixelLighting)
        {
            if (this->preferPerPixelLighting != preferPerPixelLighting)
            {
                this->preferPerPixelLighting = preferPerPixelLighting;
                this->dirtyFlags |= EffectDirtyFlags::ShaderIndex;
            }
        }

        const Matrix& BasicEffect::Projection() const
        {
            return this->projection;
        }

        void BasicEffect::Projection(const Matrix& projection)
        {
            this->projection = projection;
            this->dirtyFlags |= EffectDirtyFlags::WorldViewProj;
        }

        const Vector3& BasicEffect::SpecularColor() const
        {
            return this->specularColor;
        }

        void BasicEffect::SpecularColor(const Vector3& specularColor)
        {
            if (this->specularColor != specularColor)
            {
                this->specularColor = specularColor;

                this->specularColorParam.SetValue(this->specularColor);
            }
        }

        float BasicEffect::SpecularPower() const
        {
            return this->specularPower;
        }

        void BasicEffect::SpecularPower(const float& specularPower)
        {
            if (!Math::Equal(this->specularPower, specularPower))
            {
                this->specularPower = specularPower;

                this->specularPowerParam.SetValue(this->specularPower);
            }
        }

        const std::shared_ptr<Texture2D>& BasicEffect::Texture() const
        {
            return this->texture;
        }

        void BasicEffect::Texture(const std::shared_ptr<Texture2D>& texture)
        {
            if (this->texture != texture)
            {
                this->texture = texture;
                this->dirtyFlags |= EffectDirtyFlags::ShaderIndex;
            }
        }

        bool BasicEffect::TextureEnabled() const
        {
            return this->textureEnabled;
        }

        void BasicEffect::TextureEnabled(const bool& textureEnabled)
        {
            if (this->textureEnabled != textureEnabled)
            {
                this->textureEnabled = textureEnabled;
                this->dirtyFlags |= EffectDirtyFlags::ShaderIndex;
            }
        }

        const Matrix& BasicEffect::View() const
        {
            return this->view;
        }

        void BasicEffect::View(const Matrix& view)
        {
            this->view = view;
            this->dirtyFlags |= EffectDirtyFlags::WorldViewProj | EffectDirtyFlags::EyePosition | EffectDirtyFlags::Fog;
        }

        bool BasicEffect::VertexColorEnabled() const
        {
            return this->vertexColorEnabled;
        }

        void BasicEffect::VertexColorEnabled(const bool& vertexColorEnabled)
        {
            if (this->vertexColorEnabled != vertexColorEnabled)
            {
                this->vertexColorEnabled = vertexColorEnabled;
                this->dirtyFlags |= EffectDirtyFlags::ShaderIndex;
            }
        }

        const Matrix& BasicEffect::World() const
        {
            return this->world;
        }

        void BasicEffect::World(const Matrix& world)
        {
            this->world = world;
            this->dirtyFlags |= EffectDirtyFlags::World | EffectDirtyFlags::WorldViewProj | EffectDirtyFlags::Fog;
        }

        void BasicEffect::End()
        {
            if (this->textureEnabled)
            {
                this->texture->Deactivate();
            }

            Effect::End();
        }

        void BasicEffect::OnApply()
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

                if (!fogEnabled)
                {
                    this->shaderIndex += 1;
                }

                if (vertexColorEnabled)
                {
                    this->shaderIndex += 2;
                }

                if (this->textureEnabled)
                {
                    this->shaderIndex += 4;
                }

                if (this->lightingEnabled)
                {
                    if (this->preferPerPixelLighting)
                    {
                        this->shaderIndex += 24;
                    }
                    else if (this->oneLight)
                    {
                        this->shaderIndex += 16;
                    }
                    else
                    {
                        this->shaderIndex += 8;
                    }
                }

                this->dirtyFlags &= ~EffectDirtyFlags::ShaderIndex;
            }
        }

        void BasicEffect::CreateShader()
        {
            const auto& includes = std::vector<std::string> { ShaderManager::BasicEffectIncludePath
                                                            , ShaderManager::StructuresIncludePath
                                                            , ShaderManager::CommonIncludePath
                                                            , ShaderManager::LightingIncludePath };

            this->AddShader(u"VSBasicEffect", ShaderType::Vertex, Resources::BasicEffect_vertString, includes);
            this->AddShader(u"FSBasicEffect", ShaderType::Fragment, Resources::BasicEffect_fragString, includes);
            this->Build();
        }

        void BasicEffect::CacheEffectParameters()
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

            /*
            this->light0 = DirectionalLight { this->parameters[u"DirLight0Direction"].GetValueVector3()
                                            , this->parameters[u"DirLight0DiffuseColor"].GetValueVector3()
                                            , this->parameters[u"DirLight0SpecularColor"].GetValueVector3() };

            this->light1 = DirectionalLight { this->parameters[u"DirLight1Direction"].GetValueVector3()
                                            , this->parameters[u"DirLight1DiffuseColor"].GetValueVector3()
                                            , this->parameters[u"DirLight1SpecularColor"].GetValueVector3() };

            this->light2 = DirectionalLight { this->parameters[u"DirLight2Direction"].GetValueVector3()
                                            , this->parameters[u"DirLight2DiffuseColor"].GetValueVector3()
                                            , this->parameters[u"DirLight2SpecularColor"].GetValueVector3() };
            */
        }

        std::uint32_t BasicEffect::VSIndices[32] =
        {
            0,      // basic
            1,      // no fog
            2,      // vertex color
            3,      // vertex color, no fog
            4,      // texture
            5,      // texture, no fog
            6,      // texture + vertex color
            7,      // texture + vertex color, no fog

            8,      // vertex lighting
            8,      // vertex lighting, no fog
            9,      // vertex lighting + vertex color
            9,      // vertex lighting + vertex color, no fog
            10,     // vertex lighting + texture
            10,     // vertex lighting + texture, no fog
            11,     // vertex lighting + texture + vertex color
            11,     // vertex lighting + texture + vertex color, no fog

            12,     // one light
            12,     // one light, no fog
            13,     // one light + vertex color
            13,     // one light + vertex color, no fog
            14,     // one light + texture
            14,     // one light + texture, no fog
            15,     // one light + texture + vertex color
            15,     // one light + texture + vertex color, no fog

            16,     // pixel lighting
            16,     // pixel lighting, no fog
            17,     // pixel lighting + vertex color
            17,     // pixel lighting + vertex color, no fog
            18,     // pixel lighting + texture
            18,     // pixel lighting + texture, no fog
            19,     // pixel lighting + texture + vertex color
            19,     // pixel lighting + texture + vertex color, no fog
        };

        std::uint32_t BasicEffect::PSIndices[32] =
        {
            0,      // basic
            1,      // no fog
            0,      // vertex color
            1,      // vertex color, no fog
            2,      // texture
            3,      // texture, no fog
            2,      // texture + vertex color
            3,      // texture + vertex color, no fog

            4,      // vertex lighting
            5,      // vertex lighting, no fog
            4,      // vertex lighting + vertex color
            5,      // vertex lighting + vertex color, no fog
            6,      // vertex lighting + texture
            7,      // vertex lighting + texture, no fog
            6,      // vertex lighting + texture + vertex color
            7,      // vertex lighting + texture + vertex color, no fog

            4,      // one light
            5,      // one light, no fog
            4,      // one light + vertex color
            5,      // one light + vertex color, no fog
            6,      // one light + texture
            7,      // one light + texture, no fog
            6,      // one light + texture + vertex color
            7,      // one light + texture + vertex color, no fog

            8,      // pixel lighting
            8,      // pixel lighting, no fog
            8,      // pixel lighting + vertex color
            8,      // pixel lighting + vertex color, no fog
            9,      // pixel lighting + texture
            9,      // pixel lighting + texture, no fog
            9,      // pixel lighting + texture + vertex color
            9,      // pixel lighting + texture + vertex color, no fog
        };
    }
}
