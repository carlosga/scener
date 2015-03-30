// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/SkinnedEffect.hpp>

#include <cassert>

#include <System/IO/File.hpp>
#include <Framework/Vector4.hpp>
#include <Graphics/EffectHelpers.hpp>
#include <Graphics/GraphicsDevice.hpp>
#include <Graphics/ShaderProgram.hpp>
#include <Graphics/Resources.hpp>

using namespace System;
using namespace System::IO;
using namespace SceneR::Framework;
using namespace SceneR::Graphics;

SkinnedEffect::SkinnedEffect(GraphicsDevice& graphicsDevice)
    : Effect                 { graphicsDevice }
    , alpha                  { 1.0 }
    , ambientLightColor      { Vector3::Zero }
    , boneTransforms         ( 0 )
    , diffuseColor           { Vector3::One }
    , light0      { }
    , light1      { }
    , light2      { }
    , enableDefaultLighting  { false }
    , emissiveColor          { Vector3::Zero }
    , fogEnabled             { false }
    , fogColor               { Vector3::Zero }
    , fogEnd                 { 1.0f }
    , fogStart               { 0.0f }
    , preferPerPixelLighting { false }
    , projection             { Matrix::Identity }
    , specularColor          { Vector3::One }
    , specularPower          { 16.0f }
    , textureEnabled         { false }
    , texture                { nullptr }
    , view                   { Matrix::Identity }
    , weightsPerVertex       { 2 }
    , world                  { Matrix::Identity }
    , worldView                  { Matrix::Identity }
    , oneLight                   { false }
    , shaderIndex                { 0 }
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
    , enableDefaultLighting      { effect.enableDefaultLighting }
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
{
    this->Name(u"BasicEffect");

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

const Single& SkinnedEffect::Alpha() const
{
    return this->alpha;
}

void SkinnedEffect::Alpha(const Single& alpha)
{
    this->alpha = alpha;
}

const Vector3& SkinnedEffect::AmbientLightColor() const
{
    return this->ambientLightColor;
}

void SkinnedEffect::AmbientLightColor(const Vector3& ambientLightColor)
{
    this->ambientLightColor = ambientLightColor;
}

const Vector3& SkinnedEffect::DiffuseColor() const
{
    return this->diffuseColor;
}

void SkinnedEffect::DiffuseColor(const Vector3& diffuseColor)
{
    this->diffuseColor = diffuseColor;
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
    this->LightingEnabled(true);

    this->AmbientLightColor(EffectHelpers::EnableDefaultLighting(this->light0, this->light1, this->light2));
}

const Vector3& SkinnedEffect::EmissiveColor() const
{
    return this->emissiveColor;
}

void SkinnedEffect::EmissiveColor(const Vector3& emissiveColor)
{
    this->emissiveColor = emissiveColor;
}

const Vector3& SkinnedEffect::FogColor() const
{
    return this->fogColor;
}

void SkinnedEffect::FogColor(const Vector3& fogColor)
{
    this->fogColor = fogColor;
}

const Boolean& SkinnedEffect::FogEnabled() const
{
    return this->fogEnabled;
}

void SkinnedEffect::FogEnabled(const Boolean& fogEnabled)
{
    this->fogEnabled = fogEnabled;
}

const Single& SkinnedEffect::FogEnd() const
{
    return this->fogEnd;
}

void SkinnedEffect::FogEnd(const Single& fogEnd)
{
    this->fogEnd = fogEnd;
}

const Single& SkinnedEffect::FogStart() const
{
    return this->fogStart;
}

void SkinnedEffect::FogStart(const Single& fogStart)
{
    this->fogStart = fogStart;
}

const Boolean& SkinnedEffect::LightingEnabled() const
{
    return this->enableDefaultLighting;
}

void SkinnedEffect::LightingEnabled(const Boolean& lightingEnabled)
{
    this->enableDefaultLighting = lightingEnabled;
}

const Boolean& SkinnedEffect::PreferPerPixelLighting() const
{
    return this->preferPerPixelLighting;
}

void SkinnedEffect::PreferPerPixelLighting(const Boolean& preferPerPixelLighting)
{
    this->preferPerPixelLighting = preferPerPixelLighting;
}

const Matrix& SkinnedEffect::Projection() const
{
    return this->projection;
}

void SkinnedEffect::Projection(const Matrix& projection)
{
    this->projection = projection;
}

const Vector3& SkinnedEffect::SpecularColor() const
{
    return this->specularColor;
}

void SkinnedEffect::SpecularColor(const Vector3& specularColor)
{
    this->specularColor = specularColor;
}

const Single& SkinnedEffect::SpecularPower() const
{
    return this->specularPower;
}

void SkinnedEffect::SpecularPower(const Single& specularPower)
{
    this->specularPower = specularPower;
}

const std::shared_ptr<Texture2D>& SkinnedEffect::Texture() const
{
    return this->texture;
}

void SkinnedEffect::Texture(const std::shared_ptr<Texture2D>& texture)
{
    this->texture = texture;
}

const Boolean& SkinnedEffect::TextureEnabled() const
{
    return this->textureEnabled;
}

void SkinnedEffect::TextureEnabled(const Boolean& textureEnabled)
{
    this->textureEnabled = textureEnabled;
}

const Matrix& SkinnedEffect::View() const
{
    return this->view;
}

void SkinnedEffect::View(const Matrix& view)
{
    this->view = view;
}

const Matrix& SkinnedEffect::World() const
{
    return this->world;
}

void SkinnedEffect::World(const Matrix& world)
{
    this->world = world;
}

std::vector<Matrix> SkinnedEffect::GetBoneTransforms(const UInt32& count) const
{
    assert(count < this->boneTransforms.size());

    std::vector<Matrix> transforms(0);

    transforms.assign(this->boneTransforms.begin(), this->boneTransforms.begin() + count);

    return transforms;
}

void SkinnedEffect::SetBoneTransforms(const std::vector<Matrix>& boneTransforms)
{
    this->boneTransforms = boneTransforms;
}

const System::UInt32& SkinnedEffect::WeightsPerVertex() const
{
    return this->weightsPerVertex;
}

void SkinnedEffect::WeightsPerVertex(const System::UInt32& weightsPerVertex)
{
    assert(weightsPerVertex == 1 || weightsPerVertex == 2 || weightsPerVertex == 4);

    this->weightsPerVertex = weightsPerVertex;
}

void SkinnedEffect::Begin()
{
    Effect::Begin();

    if (this->textureEnabled)
    {
        auto& sampler = this->CurrentGraphicsDevice().SamplerStates()[0];

        this->texture->Activate();

        sampler.MaxMipLevel(this->texture->LevelCount());
        sampler.OnApply(TextureTarget::Texture2D);
    }
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
    auto emissive    = Vector3 { (this->emissiveColor + this->ambientLightColor * this->diffuseColor) * this->alpha };
    auto diffuse     = Vector4 { this->diffuseColor * this->alpha, this->alpha };
    auto viewInverse = Matrix::Invert(this->view);

    this->parameters[u"World"].SetValueTranspose(this->world);
    this->parameters[u"WorldInverseTranspose"].SetValueTranspose(Matrix::Transpose(Matrix::Invert(this->world)));
    this->parameters[u"WorldViewProj"].SetValueTranspose(this->world * this->view * this->projection);
    this->parameters[u"EyePosition"].SetValue(viewInverse.Translation());

    this->parameters[u"DiffuseColor"].SetValue(diffuse);
    this->parameters[u"EmissiveColor"].SetValue(emissive);
    this->parameters[u"SpecularColor"].SetValue(this->specularColor);
    this->parameters[u"SpecularPower"].SetValue(this->specularPower);
    this->parameters[u"WeightsPerVertex"].SetValue(this->weightsPerVertex);
    this->parameters[u"Bones"].SetValue(this->boneTransforms);

    this->parameters[u"FogVector"].SetValue(Vector4::Zero);

    if (this->enableDefaultLighting)
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

    if (this->textureEnabled)
    {
        this->parameters[u"Texture"].SetValue(*this->texture);
    }
}

void SkinnedEffect::CreateShader()
{
    const auto& includes = std::vector<std::string> { };

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
    this->textureParam               = this->parameters[u"Texture"];
    this->fogColorParam              = this->parameters[u"FogColor"];
    this->fogVectorParam             = this->parameters[u"FogVector"];
    this->eyePositionParam           = this->parameters[u"EyePosition"];
    this->worldParam                 = this->parameters[u"World"];
    this->worldViewProjParam         = this->parameters[u"WorldViewProj"];
    this->worldInverseTransposeParam = this->parameters[u"WorldInverseTranspose"];

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

    // this->parameters.Add(u"WeightsPerVertex"      , EffectParameterClass::Scalar, EffectParameterType::Int32    , this->program);
    // this->parameters.Add(u"Bones"                 , EffectParameterClass::Matrix, EffectParameterType::Single   , this->program);
}

int SkinnedEffect::VSIndices[18] =
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

int SkinnedEffect::PSIndices[18] =
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
