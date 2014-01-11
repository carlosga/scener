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

#include <Framework/Vector3.hpp>
#include <Framework/Vector4.hpp>
#include <Graphics/BasicEffect.hpp>
#include <Graphics/EffectParameter.hpp>
#include <Graphics/EffectParameterClass.hpp>
#include <Graphics/EffectParameterCollection.hpp>
#include <Graphics/EffectParameterType.hpp>
#include <Graphics/GraphicsDevice.hpp>
#include <Graphics/SamplerState.hpp>
#include <Graphics/TextureTarget.hpp>
#include <System/IO/File.hpp>

using namespace System;
using namespace System::IO;
using namespace SceneR::Framework;
using namespace SceneR::Graphics;

String BasicEffect::VSSource = File::ReadAllText(u"/home/carlos/development/projects/cpp/opengl/workspace/SceneR/Content/BasicEffect_VS.glsl");
String BasicEffect::FSSource = File::ReadAllText(u"/home/carlos/development/projects/cpp/opengl/workspace/SceneR/Content/BasicEffect_FS.glsl");

BasicEffect::BasicEffect(GraphicsDevice& graphicsDevice)
    : Effect(graphicsDevice, BasicEffect::VSSource, BasicEffect::FSSource),
      alpha(1.0),
      ambientLightColor(Vector3::Zero),
      diffuseColor(Vector3::One),
      directionalLight0(nullptr),
      directionalLight1(nullptr),
      directionalLight2(nullptr),
      enableDefaultLighting(false),
      emissiveColor(Vector3::Zero),
      fogEnabled(false),
      fogColor(Vector3::Zero),
      fogEnd(1.0f),
      fogStart(0.0f),
      preferPerPixelLighting(false),
      projection(Matrix::Identity),
      specularColor(Vector3::One),
      specularPower(16.0f),
      textureEnabled(false),
      texture(nullptr),
      vertexColorEnabled(false),
      view(Matrix::Identity),
      world(Matrix::Identity)
{
    this->Initialize();
}

BasicEffect::BasicEffect(const BasicEffect& effect)
    : Effect(effect),
      alpha(effect.alpha),
      ambientLightColor(effect.ambientLightColor),
      diffuseColor(effect.diffuseColor),
      directionalLight0(effect.directionalLight0),
      directionalLight1(effect.directionalLight1),
      directionalLight2(effect.directionalLight2),
      enableDefaultLighting(effect.enableDefaultLighting),
      emissiveColor(effect.emissiveColor),
      fogEnabled(effect.fogEnabled),
      fogColor(effect.fogColor),
      fogEnd(effect.fogEnd),
      fogStart(effect.fogStart),
      preferPerPixelLighting(effect.preferPerPixelLighting),
      projection(effect.projection),
      specularColor(effect.specularColor),
      specularPower(effect.specularPower),
      textureEnabled(effect.textureEnabled),
      texture(effect.texture),
      vertexColorEnabled(effect.vertexColorEnabled),
      view(effect.view),
      world(effect.world)
{
    this->Initialize();
}

BasicEffect::~BasicEffect()
{
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
    this->directionalLight0->Direction(Vector3(-0.5265408f, -0.5735765f, -0.6275069f));
    this->directionalLight0->DiffuseColor(Vector3(1.0f, 0.9607844f, 0.8078432f));
    this->directionalLight0->SpecularColor(Vector3(1.0f, 0.9607844f, 0.8078432f));
    this->directionalLight0->Enabled(true);

    // Fill light.
    this->directionalLight1 = std::make_shared<DirectionalLight>();
    this->directionalLight1->Direction(Vector3(0.7198464f, 0.3420201f, 0.6040227f));
    this->directionalLight1->DiffuseColor(Vector3(0.9647059f, 0.7607844f, 0.4078432f));
    this->directionalLight1->SpecularColor(Vector3::Zero);
    this->directionalLight1->Enabled(true);

    // Back light.
    this->directionalLight2 = std::make_shared<DirectionalLight>();
    this->directionalLight2->Direction(Vector3(0.4545195f, -0.7660444f, 0.4545195f));
    this->directionalLight2->DiffuseColor(Vector3(0.3231373f, 0.3607844f, 0.3937255f));
    this->directionalLight2->SpecularColor(Vector3(0.3231373f, 0.3607844f, 0.3937255f));
    this->directionalLight2->Enabled(true);

    this->ambientLightColor = Vector3(0.05333332f, 0.09882354f, 0.1819608f);
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

std::shared_ptr<Texture2D> BasicEffect::Texture() const
{
    return this->texture;
}

void BasicEffect::Texture(std::shared_ptr<Texture2D> texture)
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
        this->texture->Activate();
        this->CurrentGraphicsDevice().SamplerStates()[0].OnApply(TextureTarget::Texture2D, this->texture->LevelCount());
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
    Matrix viewInverse(this->view);
    Matrix worldView(this->world * this->view);
    Matrix worldViewProjection(worldView * this->projection);
    Matrix worldInverseTranspose(this->world);

    viewInverse.Invert();
    worldInverseTranspose.Invert();

    Vector3 eyePosition(viewInverse.M41(), viewInverse.M42(), viewInverse.M43());
    Vector3 emissive((this->emissiveColor + this->ambientLightColor * this->diffuseColor) * this->alpha);

    this->Parameters()[u"DiffuseColor"].SetValue(Vector4(this->DiffuseColor() * this->alpha, this->alpha));

    this->Parameters()[u"DirLight0DiffuseColor"].SetValue(this->directionalLight0->DiffuseColor());
    this->Parameters()[u"DirLight0Direction"].SetValue(this->directionalLight0->Direction());
    this->Parameters()[u"DirLight0SpecularColor"].SetValue(this->directionalLight0->SpecularColor());

    this->Parameters()[u"DirLight1DiffuseColor"].SetValue(this->directionalLight1->DiffuseColor());
    this->Parameters()[u"DirLight1Direction"].SetValue(this->directionalLight1->Direction());
    this->Parameters()[u"DirLight1SpecularColor"].SetValue(this->directionalLight1->SpecularColor());

    this->Parameters()[u"DirLight2DiffuseColor"].SetValue(this->directionalLight2->DiffuseColor());
    this->Parameters()[u"DirLight2Direction"].SetValue(this->directionalLight2->Direction());
    this->Parameters()[u"DirLight2SpecularColor"].SetValue(this->directionalLight2->SpecularColor());

    this->Parameters()[u"EmissiveColor"].SetValue(emissive);
    this->Parameters()[u"EyePosition"].SetValue(eyePosition);
    //this->Parameters()[u"FogVector"].SetValue(Vector4());
    this->Parameters()[u"SpecularColor"].SetValue(this->SpecularColor());
    this->Parameters()[u"SpecularPower"].SetValue(this->SpecularPower());

    if (this->textureEnabled)
    {
        this->Parameters()[u"Texture"].SetValue(*this->texture);
    }

    this->Parameters()[u"World"].SetValue(worldView);
    this->Parameters()[u"WorldInverseTranspose"].SetValue(worldInverseTranspose);
    this->Parameters()[u"WorldViewProj"].SetValueTranspose(worldViewProjection);
}

void BasicEffect::Initialize()
{
    this->Parameters().Add(u"DiffuseColor"          , EffectParameterClass::Vector, EffectParameterType::Single   , this->shaderProgram);
    this->Parameters().Add(u"DirLight0DiffuseColor" , EffectParameterClass::Vector, EffectParameterType::Single   , this->shaderProgram);
    this->Parameters().Add(u"DirLight0Direction"    , EffectParameterClass::Vector, EffectParameterType::Single   , this->shaderProgram);
    this->Parameters().Add(u"DirLight0SpecularColor", EffectParameterClass::Vector, EffectParameterType::Single   , this->shaderProgram);
    this->Parameters().Add(u"DirLight1DiffuseColor" , EffectParameterClass::Vector, EffectParameterType::Single   , this->shaderProgram);
    this->Parameters().Add(u"DirLight1Direction"    , EffectParameterClass::Vector, EffectParameterType::Single   , this->shaderProgram);
    this->Parameters().Add(u"DirLight1SpecularColor", EffectParameterClass::Vector, EffectParameterType::Single   , this->shaderProgram);
    this->Parameters().Add(u"DirLight2DiffuseColor" , EffectParameterClass::Vector, EffectParameterType::Single   , this->shaderProgram);
    this->Parameters().Add(u"DirLight2Direction"    , EffectParameterClass::Vector, EffectParameterType::Single   , this->shaderProgram);
    this->Parameters().Add(u"DirLight2SpecularColor", EffectParameterClass::Vector, EffectParameterType::Single   , this->shaderProgram);
    this->Parameters().Add(u"EmissiveColor"         , EffectParameterClass::Vector, EffectParameterType::Single   , this->shaderProgram);
    this->Parameters().Add(u"EyePosition"           , EffectParameterClass::Vector, EffectParameterType::Single   , this->shaderProgram);
    this->Parameters().Add(u"FogVector"             , EffectParameterClass::Vector, EffectParameterType::Single   , this->shaderProgram);
    this->Parameters().Add(u"SpecularColor"         , EffectParameterClass::Vector, EffectParameterType::Single   , this->shaderProgram);
    this->Parameters().Add(u"SpecularPower"         , EffectParameterClass::Scalar, EffectParameterType::Single   , this->shaderProgram);
    this->Parameters().Add(u"Texture"               , EffectParameterClass::Object, EffectParameterType::Texture2D, this->shaderProgram);
    this->Parameters().Add(u"World"                 , EffectParameterClass::Matrix, EffectParameterType::Single   , this->shaderProgram);
    this->Parameters().Add(u"WorldInverseTranspose" , EffectParameterClass::Matrix, EffectParameterType::Single   , this->shaderProgram);
    this->Parameters().Add(u"WorldViewProj"         , EffectParameterClass::Matrix, EffectParameterType::Single   , this->shaderProgram);
}
