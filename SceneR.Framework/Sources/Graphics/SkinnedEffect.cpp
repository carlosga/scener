// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/SkinnedEffect.hpp>

#include <cassert>

#include <System/IO/File.hpp>
#include <Framework/Vector4.hpp>
#include <Graphics/EffectParameter.hpp>
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
    , directionalLight0      { }
    , directionalLight1      { }
    , directionalLight2      { }
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
{
    this->CreateShader();
    this->Initialize();
}

SkinnedEffect::SkinnedEffect(const SkinnedEffect& effect)
    : Effect                 { effect }
    , alpha                  { effect.alpha }
    , ambientLightColor      { effect.ambientLightColor }
    , boneTransforms         { effect.boneTransforms }
    , diffuseColor           { effect.diffuseColor }
    , directionalLight0      { effect.directionalLight0 }
    , directionalLight1      { effect.directionalLight1 }
    , directionalLight2      { effect.directionalLight2 }
    , enableDefaultLighting  { effect.enableDefaultLighting }
    , emissiveColor          { effect.emissiveColor }
    , fogEnabled             { effect.fogEnabled }
    , fogColor               { effect.fogColor }
    , fogEnd                 { effect.fogEnd }
    , fogStart               { effect.fogStart }
    , preferPerPixelLighting { effect.preferPerPixelLighting }
    , projection             { effect.projection }
    , specularColor          { effect.specularColor }
    , specularPower          { effect.specularPower }
    , textureEnabled         { effect.textureEnabled }
    , texture                { effect.texture }
    , view                   { effect.view }
    , weightsPerVertex       { effect.weightsPerVertex }
    , world                  { effect.world }
{
    this->Initialize();
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
    return this->directionalLight0;
}

const DirectionalLight& SkinnedEffect::DirectionalLight1() const
{
    return this->directionalLight1;
}

const DirectionalLight& SkinnedEffect::DirectionalLight2() const
{
    return this->directionalLight2;
}

void SkinnedEffect::EnableDefaultLighting()
{
    // http://blogs.msdn.com/b/shawnhar/archive/2007/04/09/the-standard-lighting-rig.aspx

    this->enableDefaultLighting = true;

    // Key light.
    this->directionalLight0.Direction({ -0.5265408f, -0.5735765f, -0.6275069f });
    this->directionalLight0.DiffuseColor({ 1.0f, 0.9607844f, 0.8078432f });
    this->directionalLight0.SpecularColor({ 1.0f, 0.9607844f, 0.8078432f });
    this->directionalLight0.Enabled(true);

    // Fill light.
    this->directionalLight1.Direction({ 0.7198464f, 0.3420201f, 0.6040227f });
    this->directionalLight1.DiffuseColor({ 0.9647059f, 0.7607844f, 0.4078432f });
    this->directionalLight1.SpecularColor(Vector3::Zero);
    this->directionalLight1.Enabled(true);

    // Back light.
    this->directionalLight2.Direction({ 0.4545195f, -0.7660444f, 0.4545195f });
    this->directionalLight2.DiffuseColor({ 0.3231373f, 0.3607844f, 0.3937255f });
    this->directionalLight2.SpecularColor({ 0.3231373f, 0.3607844f, 0.3937255f });
    this->directionalLight2.Enabled(true);

    this->ambientLightColor = { 0.05333332f, 0.09882354f, 0.1819608f };
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
        if (this->directionalLight0.Enabled())
        {
            this->parameters[u"DirLight0Direction"].SetValue(this->directionalLight0.Direction());
            this->parameters[u"DirLight0DiffuseColor"].SetValue(this->directionalLight0.DiffuseColor());
            this->parameters[u"DirLight0SpecularColor"].SetValue(this->directionalLight0.SpecularColor());
        }

        if (this->directionalLight1.Enabled())
        {
            this->parameters[u"DirLight1Direction"].SetValue(this->directionalLight1.Direction());
            this->parameters[u"DirLight1DiffuseColor"].SetValue(this->directionalLight1.DiffuseColor());
            this->parameters[u"DirLight1SpecularColor"].SetValue(this->directionalLight1.SpecularColor());
        }

        if (this->directionalLight2.Enabled())
        {
            this->parameters[u"DirLight2Direction"].SetValue(this->directionalLight2.Direction());
            this->parameters[u"DirLight2DiffuseColor"].SetValue(this->directionalLight2.DiffuseColor());
            this->parameters[u"DirLight2SpecularColor"].SetValue(this->directionalLight2.SpecularColor());
        }
    }

    if (this->textureEnabled)
    {
        this->parameters[u"Texture"].SetValue(*this->texture);
    }
}

void SkinnedEffect::CreateShader()
{
    this->program = std::make_shared<ShaderProgram>(u"SkinnedEffect");
    this->program->AddShader(u"VSSkinnedEffect", ShaderType::Vertex, Resources::SkinnedEffect_vertString);
    this->program->AddShader(u"FSSkinnedEffect", ShaderType::Fragment, Resources::SkinnedEffect_fragString);
    this->program->Build();
}

void SkinnedEffect::Initialize()
{
    this->parameters.Add(u"EyePosition"           , EffectParameterClass::Vector, EffectParameterType::Single   , this->program);
    this->parameters.Add(u"World"                 , EffectParameterClass::Matrix, EffectParameterType::Single   , this->program);
    this->parameters.Add(u"WorldInverseTranspose" , EffectParameterClass::Matrix, EffectParameterType::Single   , this->program);
    this->parameters.Add(u"WorldViewProj"         , EffectParameterClass::Matrix, EffectParameterType::Single   , this->program);
    this->parameters.Add(u"DiffuseColor"          , EffectParameterClass::Vector, EffectParameterType::Single   , this->program);
    this->parameters.Add(u"EmissiveColor"         , EffectParameterClass::Vector, EffectParameterType::Single   , this->program);
    this->parameters.Add(u"SpecularColor"         , EffectParameterClass::Vector, EffectParameterType::Single   , this->program);
    this->parameters.Add(u"SpecularPower"         , EffectParameterClass::Scalar, EffectParameterType::Single   , this->program);
    this->parameters.Add(u"DirLight0DiffuseColor" , EffectParameterClass::Vector, EffectParameterType::Single   , this->program);
    this->parameters.Add(u"DirLight0Direction"    , EffectParameterClass::Vector, EffectParameterType::Single   , this->program);
    this->parameters.Add(u"DirLight0SpecularColor", EffectParameterClass::Vector, EffectParameterType::Single   , this->program);
    this->parameters.Add(u"DirLight1DiffuseColor" , EffectParameterClass::Vector, EffectParameterType::Single   , this->program);
    this->parameters.Add(u"DirLight1Direction"    , EffectParameterClass::Vector, EffectParameterType::Single   , this->program);
    this->parameters.Add(u"DirLight1SpecularColor", EffectParameterClass::Vector, EffectParameterType::Single   , this->program);
    this->parameters.Add(u"DirLight2DiffuseColor" , EffectParameterClass::Vector, EffectParameterType::Single   , this->program);
    this->parameters.Add(u"DirLight2Direction"    , EffectParameterClass::Vector, EffectParameterType::Single   , this->program);
    this->parameters.Add(u"DirLight2SpecularColor", EffectParameterClass::Vector, EffectParameterType::Single   , this->program);
    this->parameters.Add(u"Texture"               , EffectParameterClass::Object, EffectParameterType::Texture2D, this->program);
    this->parameters.Add(u"WeightsPerVertex"      , EffectParameterClass::Scalar, EffectParameterType::Int32    , this->program);
    this->parameters.Add(u"Bones"                 , EffectParameterClass::Matrix, EffectParameterType::Single   , this->program);
    this->parameters.Add(u"FogVector"             , EffectParameterClass::Vector, EffectParameterType::Single   , this->program);
}
