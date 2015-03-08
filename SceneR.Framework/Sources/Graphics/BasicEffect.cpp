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
#include <Framework/Vector4.hpp>
#include <Graphics/EffectHelpers.hpp>
#include <Graphics/EffectParameter.hpp>
#include <Graphics/GraphicsDevice.hpp>
#include <Graphics/ShaderManager.hpp>
#include <Graphics/ShaderProgram.hpp>
#include <Graphics/Resources.hpp>

using namespace System;
using namespace SceneR::Framework;
using namespace SceneR::Graphics;

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
    , dirtyFlags                 { EffectDirtyFlags::All }
    , textureParam               { }
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
    , shaderIndexParam           { }
{
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
    , dirtyFlags                 { EffectDirtyFlags::All }
    , textureParam               { }
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
    , shaderIndexParam           { }
{
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

const Single& BasicEffect::Alpha() const
{
    return this->alpha;
}

void BasicEffect::Alpha(const Single& alpha)
{
    if (this->alpha != alpha)
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
    }
}

const Boolean& BasicEffect::FogEnabled() const
{
    return this->fogEnabled;
}

void BasicEffect::FogEnabled(const Boolean& fogEnabled)
{
    if (this->fogEnabled != fogEnabled)
    {
        this->fogEnabled = fogEnabled;
        this->dirtyFlags |= EffectDirtyFlags::Fog;
    }
}

const Single& BasicEffect::FogEnd() const
{
    return this->fogEnd;
}

void BasicEffect::FogEnd(const Single& fogEnd)
{
    if (this->fogEnd != fogEnd)
    {
        this->fogEnd = fogEnd;
        this->dirtyFlags |= EffectDirtyFlags::Fog;
    }
}

const Single& BasicEffect::FogStart() const
{
    return this->fogStart;
}

void BasicEffect::FogStart(const Single& fogStart)
{
    if (this->fogStart != fogStart)
    {
        this->fogStart = fogStart;
        this->dirtyFlags |= EffectDirtyFlags::Fog;
    }
}

const Boolean& BasicEffect::LightingEnabled() const
{
    return this->lightingEnabled;
}

void BasicEffect::LightingEnabled(const Boolean& lightingEnabled)
{
    if (this->lightingEnabled != lightingEnabled)
    {
        this->lightingEnabled = lightingEnabled;
        this->dirtyFlags |= EffectDirtyFlags::ShaderIndex | EffectDirtyFlags::MaterialColor;
    }
}

const Boolean& BasicEffect::PreferPerPixelLighting() const
{
    return this->preferPerPixelLighting;
}

void BasicEffect::PreferPerPixelLighting(const Boolean& preferPerPixelLighting)
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
    this->specularColor = specularColor;
}

const Single& BasicEffect::SpecularPower() const
{
    return this->specularPower;
}

void BasicEffect::SpecularPower(const Single& specularPower)
{
    this->specularPower = specularPower;
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

const Boolean& BasicEffect::TextureEnabled() const
{
    return this->textureEnabled;
}

void BasicEffect::TextureEnabled(const Boolean& textureEnabled)
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

const Boolean& BasicEffect::VertexColorEnabled() const
{
    return this->vertexColorEnabled;
}

void BasicEffect::VertexColorEnabled(const Boolean& vertexColorEnabled)
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

void BasicEffect::Begin()
{
    Effect::Begin();

    if (this->textureEnabled)
    {
        SamplerState& sampler = this->CurrentGraphicsDevice().SamplerStates()[0];

        this->texture->Activate();

        sampler.MaxMipLevel(this->texture->LevelCount());
        sampler.OnApply(TextureTarget::Texture2D);
    }
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
    // Recompute the world+view+projection matrix or fog vector?
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
        this->parameters[u"SpecularColor"].SetValue(this->specularColor);
        this->parameters[u"SpecularPower"].SetValue(this->specularPower);

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

        if (oneLight != newOneLight)
        {
            oneLight = newOneLight;
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

    if (this->textureEnabled)
    {
        this->parameters[u"Texture"].SetValue(*this->texture);
    }

    // Recompute the shader index?
    if ((this->dirtyFlags & EffectDirtyFlags::ShaderIndex) != 0)
    {
        int shaderIndex = 0;

        if (!fogEnabled)
        {
            shaderIndex += 1;
        }

        if (vertexColorEnabled)
        {
            shaderIndex += 2;
        }

        if (this->textureEnabled)
        {
            shaderIndex += 4;
        }

        if (this->lightingEnabled)
        {
            if (this->preferPerPixelLighting)
            {
                shaderIndex += 24;
            }
            else if (this->oneLight)
            {
                shaderIndex += 16;
            }
            else
            {
                shaderIndex += 8;
            }
        }

        // this->shaderIndexParam.SetValue(shaderIndex);

        this->dirtyFlags &= ~EffectDirtyFlags::ShaderIndex;
    }
}

void BasicEffect::CreateShader()
{
    const auto& includes = std::vector<std::string > { ShaderManager::BasicEffectIncludePath
                                                     , ShaderManager::StructuresIncludePath
                                                     , ShaderManager::CommonIncludePath
                                                     , ShaderManager::LightingIncludePath };

    this->shader = std::make_shared<ShaderProgram>();
    this->shader->AddShader(u"VSBasicEffect", ShaderType::Vertex, Resources::BasicEffect_vertString, includes);
    this->shader->AddShader(u"FSBasicEffect", ShaderType::Fragment, Resources::BasicEffect_fragString, includes);
    this->shader->Build();
}

void BasicEffect::CacheEffectParameters()
{
    this->diffuseColorParam  = this->parameters.Add(u"DiffuseColor"  , EffectParameterClass::Vector, EffectParameterType::Single   , this->shader);
    this->emissiveColorParam = this->parameters.Add(u"EmissiveColor" , EffectParameterClass::Vector, EffectParameterType::Single   , this->shader);
    this->specularColorParam = this->parameters.Add(u"SpecularColor" , EffectParameterClass::Vector, EffectParameterType::Single   , this->shader);
    this->specularPowerParam = this->parameters.Add(u"SpecularPower" , EffectParameterClass::Scalar, EffectParameterType::Single   , this->shader);
    this->textureParam       = this->parameters.Add(u"Texture"       , EffectParameterClass::Object, EffectParameterType::Texture2D, this->shader);
    this->fogColorParam      = this->parameters.Add(u"FogColor"      , EffectParameterClass::Vector, EffectParameterType::Single   , this->shader);
    this->fogVectorParam     = this->parameters.Add(u"FogVector"     , EffectParameterClass::Vector, EffectParameterType::Single   , this->shader);
    this->eyePositionParam   = this->parameters.Add(u"EyePosition"   , EffectParameterClass::Vector, EffectParameterType::Single   , this->shader);
    // this->shaderIndexParam   = this->parameters.Add(u"ShaderIndex"   , EffectParameterClass::Scalar, EffectParameterType::Int32    , this->shader);
    this->worldParam         = this->parameters.Add(u"World"         , EffectParameterClass::Matrix, EffectParameterType::Single   , this->shader);
    this->worldViewProjParam = this->parameters.Add(u"WorldViewProj" , EffectParameterClass::Matrix, EffectParameterType::Single   , this->shader);
    this->worldInverseTransposeParam = this->parameters.Add(u"WorldInverseTranspose" , EffectParameterClass::Matrix, EffectParameterType::Single, this->shader);

    this->parameters.Add(u"DirLight0DiffuseColor" , EffectParameterClass::Vector, EffectParameterType::Single, this->shader);
    this->parameters.Add(u"DirLight0Direction"    , EffectParameterClass::Vector, EffectParameterType::Single, this->shader);
    this->parameters.Add(u"DirLight0SpecularColor", EffectParameterClass::Vector, EffectParameterType::Single, this->shader);
    this->parameters.Add(u"DirLight1DiffuseColor" , EffectParameterClass::Vector, EffectParameterType::Single, this->shader);
    this->parameters.Add(u"DirLight1Direction"    , EffectParameterClass::Vector, EffectParameterType::Single, this->shader);
    this->parameters.Add(u"DirLight1SpecularColor", EffectParameterClass::Vector, EffectParameterType::Single, this->shader);
    this->parameters.Add(u"DirLight2DiffuseColor" , EffectParameterClass::Vector, EffectParameterType::Single, this->shader);
    this->parameters.Add(u"DirLight2Direction"    , EffectParameterClass::Vector, EffectParameterType::Single, this->shader);
    this->parameters.Add(u"DirLight2SpecularColor", EffectParameterClass::Vector, EffectParameterType::Single, this->shader);

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
