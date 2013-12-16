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
#include <Graphics/DirectionalLight.hpp>
#include <Graphics/EffectParameter.hpp>
#include <Graphics/EffectParameterClass.hpp>
#include <Graphics/EffectParameterType.hpp>
#include <System/IO/File.hpp>
#include <string>

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
      lightingEnabled(true),
      emissiveColor(0.0f, 0.0f, 0.0f, 1.0f),
      fogEnabled(false),
      fogColor(0.0f, 0.0f, 0.0f, 1.0f),
      fogEnd(0.0f),
      fogStart(0.0f),
      preferPerPixelLighting(false),
      projection(Matrix::Identity),
      specularColor(0.0f, 0.0f, 0.0f, 1.0f),
      specularPower(0.0f),
      textureEnabled(true),
      texture(nullptr),
      vertexColorEnabled(false),
      view(Matrix::Identity),
      world(Matrix::Identity)
{
}

BasicEffect::BasicEffect(const BasicEffect& effect)
    : Effect(effect),
      alpha(effect.alpha),
      ambientLightColor(effect.ambientLightColor),
      diffuseColor(effect.diffuseColor),
      directionalLight0(effect.directionalLight0),
      directionalLight1(effect.directionalLight1),
      directionalLight2(effect.directionalLight2),
      lightingEnabled(effect.lightingEnabled),
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

const Color& BasicEffect::AmbientLightColor() const
{
    return this->ambientLightColor;
}

void BasicEffect::AmbientLightColor(const Color& ambientLightColor)
{
    this->ambientLightColor = ambientLightColor;
}

const Color& BasicEffect::DiffuseColor() const
{
    return this->diffuseColor;
}

void BasicEffect::DiffuseColor(const Color& diffuseColor)
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

const Color& BasicEffect::EmissiveColor() const
{
    return this->emissiveColor;
}

void BasicEffect::EmissiveColor(const Color& emissiveColor)
{
    this->emissiveColor = emissiveColor;
}

const Color& BasicEffect::FogColor() const
{
    return this->fogColor;
}

void BasicEffect::FogColor(const Color& fogColor)
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
    return this->lightingEnabled;
}

void BasicEffect::LightingEnabled(const Boolean& lightingEnabled)
{
    this->lightingEnabled = lightingEnabled;
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

const Color& BasicEffect::SpecularColor() const
{
    return this->specularColor;
}

void BasicEffect::SpecularColor(const Color& specularColor)
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
    this->lightingEnabled = true;

    this->ambientLightColor = Color(0.053f, 0.098f, 0.181f);
    this->specularColor     = Color(0.0f, 0.0f, 0.0f);
    this->diffuseColor      = Color(0.64f, 0.64f, 0.64f);

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
    Matrix worldViewProjection(worldView * this->projection);

    worldInverseTranspose.Invert();
    worldInverseTranspose.Transpose();

    auto& parameters = this->Parameters();

    /*
     * Ka
     * Kd
     * Ks
     * LightIntensity
     * LightPosition
     * Shininess
     * WorldInverseTranspose
     * WorldView
     * WorldViewProjection
     */

    parameters[u"WorldView"].SetValue(worldView);
    parameters[u"WorldViewProjection"].SetValue(Matrix::Transpose(worldViewProjection));
    parameters[u"WorldInverseTranspose"].SetValue(worldInverseTranspose);
    parameters[u"DirectionalLight0"].SetValue(this->directionalLight0.get());
    parameters[u"DirectionalLight1"].SetValue(this->directionalLight1.get());
    parameters[u"DirectionalLight2"].SetValue(this->directionalLight2.get());
}
