// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/BasicEffect.hpp>

#include <System/IO/File.hpp>
#include <Framework/Vector4.hpp>
#include <Graphics/EffectParameter.hpp>
#include <Graphics/GraphicsDevice.hpp>

using namespace System;
using namespace System::IO;
using namespace SceneR::Framework;
using namespace SceneR::Graphics;

const String BasicEffect::VSSource = File::ReadAllText(u"/home/carlos/development/projects/cpp/opengl/scener/SceneR/Content/BasicEffect.vert");
const String BasicEffect::FSSource = File::ReadAllText(u"/home/carlos/development/projects/cpp/opengl/scener/SceneR/Content/BasicEffect.frag");

BasicEffect::BasicEffect(GraphicsDevice& graphicsDevice)
    : Effect                 { graphicsDevice, BasicEffect::VSSource, BasicEffect::FSSource }
    , alpha                  { 1.0f }
    , ambientLightColor      { Vector3::Zero }
    , diffuseColor           { Vector3::One }
    , directionalLight0      { nullptr }
    , directionalLight1      { nullptr }
    , directionalLight2      { nullptr }
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
    , vertexColorEnabled     { false }
    , view                   { Matrix::Identity }
    , world                  { Matrix::Identity }
{
    this->Initialize();
}

BasicEffect::BasicEffect(const BasicEffect& effect)
    : Effect                 { effect }
    , alpha                  { effect.alpha }
    , ambientLightColor      { effect.ambientLightColor }
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
    , vertexColorEnabled     { effect.vertexColorEnabled }
    , view                   { effect.view }
    , world                  { effect.world }
{
    this->Initialize();
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
    this->alpha = alpha;
}

const Vector3& BasicEffect::AmbientLightColor() const
{
    return this->ambientLightColor;
}

void BasicEffect::AmbientLightColor(const Vector3& ambientLightColor)
{
    this->ambientLightColor = ambientLightColor;
}

const Vector3& BasicEffect::DiffuseColor() const
{
    return this->diffuseColor;
}

void BasicEffect::DiffuseColor(const Vector3& diffuseColor)
{
    this->diffuseColor = diffuseColor;
}

const std::shared_ptr<DirectionalLight>& BasicEffect::DirectionalLight0() const
{
    return this->directionalLight0;
}

void BasicEffect::DirectionalLight0(const std::shared_ptr<DirectionalLight>& directionalLight)
{
    this->directionalLight0 = directionalLight;
}

const std::shared_ptr<DirectionalLight>& BasicEffect::DirectionalLight1() const
{
    return this->directionalLight1;
}

void BasicEffect::DirectionalLight1(const std::shared_ptr<DirectionalLight>& directionalLight)
{
    this->directionalLight1 = directionalLight;
}

const std::shared_ptr<DirectionalLight>& BasicEffect::DirectionalLight2() const
{
    return this->directionalLight2;
}

void BasicEffect::DirectionalLight2(const std::shared_ptr<DirectionalLight>& directionalLight)
{
    this->directionalLight2 = directionalLight;
}

void BasicEffect::EnableDefaultLighting()
{
    // http://blogs.msdn.com/b/shawnhar/archive/2007/04/09/the-standard-lighting-rig.aspx

    this->enableDefaultLighting = true;

    // Key light.
    this->directionalLight0 = std::make_shared<DirectionalLight>();
    this->directionalLight0->Direction({ -0.5265408f, -0.5735765f, -0.6275069f });
    this->directionalLight0->DiffuseColor({ 1.0f, 0.9607844f, 0.8078432f });
    this->directionalLight0->SpecularColor({ 1.0f, 0.9607844f, 0.8078432f });
    this->directionalLight0->Enabled(true);

    // Fill light.
    this->directionalLight1 = std::make_shared<DirectionalLight>();
    this->directionalLight1->Direction({ 0.7198464f, 0.3420201f, 0.6040227f });
    this->directionalLight1->DiffuseColor({ 0.9647059f, 0.7607844f, 0.4078432f });
    this->directionalLight1->SpecularColor(Vector3::Zero);
    this->directionalLight1->Enabled(true);

    // Back light.
    this->directionalLight2 = std::make_shared<DirectionalLight>();
    this->directionalLight2->Direction({ 0.4545195f, -0.7660444f, 0.4545195f });
    this->directionalLight2->DiffuseColor({ 0.3231373f, 0.3607844f, 0.3937255f });
    this->directionalLight2->SpecularColor({ 0.3231373f, 0.3607844f, 0.3937255f });
    this->directionalLight2->Enabled(true);

    this->ambientLightColor = { 0.05333332f, 0.09882354f, 0.1819608f };
}

const Vector3& BasicEffect::EmissiveColor() const
{
    return this->emissiveColor;
}

void BasicEffect::EmissiveColor(const Vector3& emissiveColor)
{
    this->emissiveColor = emissiveColor;
}

const Vector3& BasicEffect::FogColor() const
{
    return this->fogColor;
}

void BasicEffect::FogColor(const Vector3& fogColor)
{
    this->fogColor = fogColor;
}

const Boolean& BasicEffect::FogEnabled() const
{
    return this->fogEnabled;
}

void BasicEffect::FogEnabled(const Boolean& fogEnabled)
{
    this->fogEnabled = fogEnabled;
}

const Single& BasicEffect::FogEnd() const
{
    return this->fogEnd;
}

void BasicEffect::FogEnd(const Single& fogEnd)
{
    this->fogEnd = fogEnd;
}

const Single& BasicEffect::FogStart() const
{
    return this->fogStart;
}

void BasicEffect::FogStart(const Single& fogStart)
{
    this->fogStart = fogStart;
}

const Boolean& BasicEffect::LightingEnabled() const
{
    return this->enableDefaultLighting;
}

void BasicEffect::LightingEnabled(const Boolean& lightingEnabled)
{
    this->enableDefaultLighting = lightingEnabled;
}

const Boolean& BasicEffect::PreferPerPixelLighting() const
{
    return this->preferPerPixelLighting;
}

void BasicEffect::PreferPerPixelLighting(const Boolean& preferPerPixelLighting)
{
    this->preferPerPixelLighting = preferPerPixelLighting;
}

const Matrix& BasicEffect::Projection() const
{
    return this->projection;
}

void BasicEffect::Projection(const Matrix& projection)
{
    this->projection = projection;
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
    this->texture = texture;
}

const Boolean& BasicEffect::TextureEnabled() const
{
    return this->textureEnabled;
}

void BasicEffect::TextureEnabled(const Boolean& textureEnabled)
{
    this->textureEnabled = textureEnabled;
}

const Matrix& BasicEffect::View() const
{
    return this->view;
}

void BasicEffect::View(const Matrix& view)
{
    this->view = view;
}

const Boolean& BasicEffect::VertexColorEnabled() const
{
    return this->vertexColorEnabled;
}

void BasicEffect::VertexColorEnabled(const Boolean& vertexColorEnabled)
{
    this->vertexColorEnabled = vertexColorEnabled;
}

const Matrix& BasicEffect::World() const
{
    return this->world;
}

void BasicEffect::World(const Matrix& world)
{
    this->world = world;
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
    auto viewInverse           = Matrix::Invert(this->view);
    auto worldView             = this->world * this->view;
    auto worldViewProjection   = worldView * this->projection;
    auto worldInverseTranspose = Matrix::Invert(this->world);

    auto eyePosition = Vector3 { viewInverse.M41(), viewInverse.M42(), viewInverse.M43() };
    auto emissive    = Vector3 { (this->emissiveColor + this->ambientLightColor * this->diffuseColor) * this->alpha };

    auto& parameters = this->Parameters();

    parameters[u"EyePosition"].SetValue(eyePosition);
    parameters[u"World"].SetValue(worldView);
    parameters[u"WorldInverseTranspose"].SetValue(worldInverseTranspose);
    parameters[u"WorldViewProj"].SetValueTranspose(worldViewProjection);
    parameters[u"DiffuseColor"].SetValue(Vector4 { this->diffuseColor * this->alpha, this->alpha });
    parameters[u"EmissiveColor"].SetValue(emissive);
    parameters[u"SpecularColor"].SetValue(this->specularColor);
    parameters[u"SpecularPower"].SetValue(this->specularPower);

    //this->Parameters()[u"FogVector"].SetValue(Vector4());

    if (this->enableDefaultLighting)
    {
        if (this->directionalLight0->Enabled())
        {
            parameters[u"DirLight0Direction"].SetValue(this->directionalLight0->Direction());
            parameters[u"DirLight0DiffuseColor"].SetValue(this->directionalLight0->DiffuseColor());
            parameters[u"DirLight0SpecularColor"].SetValue(this->directionalLight0->SpecularColor());
        }

        if (this->directionalLight1->Enabled())
        {
            parameters[u"DirLight1Direction"].SetValue(this->directionalLight1->Direction());
            parameters[u"DirLight1DiffuseColor"].SetValue(this->directionalLight1->DiffuseColor());
            parameters[u"DirLight1SpecularColor"].SetValue(this->directionalLight1->SpecularColor());
        }

        if (this->directionalLight2->Enabled())
        {
            parameters[u"DirLight2Direction"].SetValue(this->directionalLight2->Direction());
            parameters[u"DirLight2DiffuseColor"].SetValue(this->directionalLight2->DiffuseColor());
            parameters[u"DirLight2SpecularColor"].SetValue(this->directionalLight2->SpecularColor());
        }
    }

    if (this->textureEnabled)
    {
        parameters[u"Texture"].SetValue(*this->texture);
    }
}

void BasicEffect::Initialize()
{
    auto& parameters = this->Parameters();

    parameters.Add(u"EyePosition"           , EffectParameterClass::Vector, EffectParameterType::Single   , this->shader);
    parameters.Add(u"World"                 , EffectParameterClass::Matrix, EffectParameterType::Single   , this->shader);
    parameters.Add(u"WorldInverseTranspose" , EffectParameterClass::Matrix, EffectParameterType::Single   , this->shader);
    parameters.Add(u"WorldViewProj"         , EffectParameterClass::Matrix, EffectParameterType::Single   , this->shader);
    parameters.Add(u"DiffuseColor"          , EffectParameterClass::Vector, EffectParameterType::Single   , this->shader);
    parameters.Add(u"EmissiveColor"         , EffectParameterClass::Vector, EffectParameterType::Single   , this->shader);
    parameters.Add(u"SpecularColor"         , EffectParameterClass::Vector, EffectParameterType::Single   , this->shader);
    parameters.Add(u"SpecularPower"         , EffectParameterClass::Scalar, EffectParameterType::Single   , this->shader);
    parameters.Add(u"DirLight0DiffuseColor" , EffectParameterClass::Vector, EffectParameterType::Single   , this->shader);
    parameters.Add(u"DirLight0Direction"    , EffectParameterClass::Vector, EffectParameterType::Single   , this->shader);
    parameters.Add(u"DirLight0SpecularColor", EffectParameterClass::Vector, EffectParameterType::Single   , this->shader);
    parameters.Add(u"DirLight1DiffuseColor" , EffectParameterClass::Vector, EffectParameterType::Single   , this->shader);
    parameters.Add(u"DirLight1Direction"    , EffectParameterClass::Vector, EffectParameterType::Single   , this->shader);
    parameters.Add(u"DirLight1SpecularColor", EffectParameterClass::Vector, EffectParameterType::Single   , this->shader);
    parameters.Add(u"DirLight2DiffuseColor" , EffectParameterClass::Vector, EffectParameterType::Single   , this->shader);
    parameters.Add(u"DirLight2Direction"    , EffectParameterClass::Vector, EffectParameterType::Single   , this->shader);
    parameters.Add(u"DirLight2SpecularColor", EffectParameterClass::Vector, EffectParameterType::Single   , this->shader);
    parameters.Add(u"Texture"               , EffectParameterClass::Object, EffectParameterType::Texture2D, this->shader);
    // this->Parameters().Add(u"FogVector"             , EffectParameterClass::Vector, EffectParameterType::Single   , this->shaderProgram);
}
