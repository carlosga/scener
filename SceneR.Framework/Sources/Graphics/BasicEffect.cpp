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

#include <Framework/Color.hpp>
#include <Framework/Vector3.hpp>
#include <Graphics/BasicEffect.hpp>
#include <Graphics/EffectParameter.hpp>
#include <Graphics/EffectParameterClass.hpp>
#include <Graphics/EffectParameterCollection.hpp>
#include <Graphics/EffectParameterType.hpp>
#include <System/IO/File.hpp>

using namespace System;
using namespace System::IO;
using namespace SceneR::Framework;
using namespace SceneR::Graphics;

String BasicEffect::VSSource = File::ReadAllText(u"/home/carlos/development/projects/cpp/opengl/workspace/SceneR/Content/BasicEffect_VS.glsl");
String BasicEffect::FSSource = File::ReadAllText(u"/home/carlos/development/projects/cpp/opengl/workspace/SceneR/Content/BasicEffect_FS.glsl");

BasicEffect::BasicEffect(GraphicsDevice& graphicsDevice)
    : Effect(graphicsDevice, BasicEffect::VSSource, BasicEffect::FSSource),
      alpha(0),
      ambientLightColor(0.053f, 0.098f, 0.181f),
      diffuseColor(0.64f, 0.64f, 0.64f),
      directionalLight0(nullptr),
      directionalLight1(nullptr),
      directionalLight2(nullptr),
      enableDefaultLighting(true),
      emissiveColor(0.0f, 0.0f, 0.0f),
      fogEnabled(false),
      fogColor(0.0f, 0.0f, 0.0f),
      fogEnd(0.0f),
      fogStart(0.0f),
      preferPerPixelLighting(false),
      projection(Matrix::Identity),
      specularColor(0.0f, 0.0f, 0.0f),
      specularPower(0.0f),
      textureEnabled(true),
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
    this->directionalLight0 = directionalLight0;
}

const std::shared_ptr<DirectionalLight>& BasicEffect::DirectionalLight1() const
{
    return this->directionalLight1;
}

void BasicEffect::DirectionalLight1(const std::shared_ptr<DirectionalLight>& directionalLight)
{
    this->directionalLight1 = directionalLight1;
}

const std::shared_ptr<DirectionalLight>& BasicEffect::DirectionalLight2() const
{
    return this->directionalLight2;
}

void BasicEffect::DirectionalLight2(const std::shared_ptr<DirectionalLight>& directionalLight)
{
    this->directionalLight2 = directionalLight2;
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

void BasicEffect::EnableDefaultLighting()
{
    this->enableDefaultLighting = true;

    this->ambientLightColor = Vector3(0.053f, 0.098f, 0.181f);
    this->specularColor     = Vector3(0.0f, 0.0f, 0.0f);
    this->diffuseColor      = Vector3(0.64f, 0.64f, 0.64f);

    this->directionalLight0 = std::make_shared<DirectionalLight>();
    this->directionalLight0->Enabled(true);
    this->directionalLight0->DiffuseColor(Color(1.0f, 0.96f, 0.81f));
    this->directionalLight0->Direction(Vector3(-0.52f, -0.57f, -0.62f));
    this->directionalLight0->SpecularColor(Color(1.0f, 0.96f, 0.81f));

    this->directionalLight1 = std::make_shared<DirectionalLight>();
    this->directionalLight1->Enabled(true);
    this->directionalLight1->DiffuseColor(Color(0.96f, 0.76f, 0.40f));
    this->directionalLight1->Direction(Vector3(0.71f, 0.34f, 0.60f));
    this->directionalLight1->SpecularColor(Color(0.0f, 0.0f, 0.0f));

    this->directionalLight2 = std::make_shared<DirectionalLight>();
    this->directionalLight2->Enabled(true);
    this->directionalLight2->DiffuseColor(Color(0.32f, 0.36f, 0.39f));
    this->directionalLight2->Direction(Vector3(0.45f, -0.76f, 0.45f));
    this->directionalLight2->SpecularColor(Color(0.32f, 0.36f, 0.39f));
}

void BasicEffect::OnApply()
{
    Matrix worldInverseTranspose(this->world);
    Matrix worldView(this->world * this->view);
    Matrix viewInverse(this->view);
    Matrix worldViewProjection(worldView * this->projection);

    viewInverse.Invert();
    worldInverseTranspose.Invert();
    worldInverseTranspose.Transpose();

    Vector3 eyePosition(viewInverse.M41(), viewInverse.M42(), viewInverse.M43());

    this->Parameters()[u"DiffuseColor"].SetValue(Vector4(this->DiffuseColor(), this->Alpha()));
    this->Parameters()[u"DirLight0DiffuseColor"].SetValue(this->directionalLight0->DiffuseColor());
    this->Parameters()[u"DirLight0Direction"].SetValue(this->directionalLight0->Direction());
    this->Parameters()[u"DirLight0SpecularColor"].SetValue(this->directionalLight0->SpecularColor());
    this->Parameters()[u"DirLight1DiffuseColor"].SetValue(this->directionalLight1->DiffuseColor());
    this->Parameters()[u"DirLight1Direction"].SetValue(this->directionalLight1->Direction());
    this->Parameters()[u"DirLight1SpecularColor"].SetValue(this->directionalLight0->SpecularColor());
    this->Parameters()[u"DirLight2DiffuseColor"].SetValue(this->directionalLight2->DiffuseColor());
    this->Parameters()[u"DirLight2Direction"].SetValue(this->directionalLight2->Direction());
    this->Parameters()[u"DirLight2SpecularColor"].SetValue(this->directionalLight0->SpecularColor());
    this->Parameters()[u"EmissiveColor"].SetValue(this->EmissiveColor());
    this->Parameters()[u"EyePosition"].SetValue(eyePosition);
    this->Parameters()[u"FogVector"].SetValue(Vector4());
    this->Parameters()[u"SpecularColor"].SetValue(this->SpecularColor());
    this->Parameters()[u"SpecularPower"].SetValue(this->SpecularPower());
    this->Parameters()[u"World"].SetValue(this->world);
    this->Parameters()[u"WorldInverseTranspose"].SetValue(worldInverseTranspose);
    this->Parameters()[u"WorldViewProj"].SetValue(worldViewProjection);
}

void BasicEffect::Initialize()
{
    this->EnableDefaultLighting();

    this->Parameters().Add(u"DiffuseColor"          , EffectParameterClass::Vector, EffectParameterType::Single, this->shaderProgram);
    this->Parameters().Add(u"DirLight0DiffuseColor" , EffectParameterClass::Vector, EffectParameterType::Single, this->shaderProgram);
    this->Parameters().Add(u"DirLight0Direction"    , EffectParameterClass::Vector, EffectParameterType::Single, this->shaderProgram);
    this->Parameters().Add(u"DirLight0SpecularColor", EffectParameterClass::Vector, EffectParameterType::Single, this->shaderProgram);
    this->Parameters().Add(u"DirLight1DiffuseColor" , EffectParameterClass::Vector, EffectParameterType::Single, this->shaderProgram);
    this->Parameters().Add(u"DirLight1Direction"    , EffectParameterClass::Vector, EffectParameterType::Single, this->shaderProgram);
    this->Parameters().Add(u"DirLight1SpecularColor", EffectParameterClass::Vector, EffectParameterType::Single, this->shaderProgram);
    this->Parameters().Add(u"DirLight2DiffuseColor" , EffectParameterClass::Vector, EffectParameterType::Single, this->shaderProgram);
    this->Parameters().Add(u"DirLight2Direction"    , EffectParameterClass::Vector, EffectParameterType::Single, this->shaderProgram);
    this->Parameters().Add(u"DirLight2SpecularColor", EffectParameterClass::Vector, EffectParameterType::Single, this->shaderProgram);
    this->Parameters().Add(u"EmissiveColor"         , EffectParameterClass::Vector, EffectParameterType::Single, this->shaderProgram);
    this->Parameters().Add(u"EyePosition"           , EffectParameterClass::Vector, EffectParameterType::Single, this->shaderProgram);
    this->Parameters().Add(u"FogVector"             , EffectParameterClass::Vector, EffectParameterType::Single, this->shaderProgram);
    this->Parameters().Add(u"SpecularColor"         , EffectParameterClass::Vector, EffectParameterType::Single, this->shaderProgram);
    this->Parameters().Add(u"SpecularPower"         , EffectParameterClass::Scalar, EffectParameterType::Single, this->shaderProgram);
    this->Parameters().Add(u"World"                 , EffectParameterClass::Matrix, EffectParameterType::Single, this->shaderProgram);
    this->Parameters().Add(u"WorldInverseTranspose" , EffectParameterClass::Matrix, EffectParameterType::Single, this->shaderProgram);
    this->Parameters().Add(u"WorldViewProj"         , EffectParameterClass::Matrix, EffectParameterType::Single, this->shaderProgram);
}
