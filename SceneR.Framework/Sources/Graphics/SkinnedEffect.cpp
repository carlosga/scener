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

#include <Framework/Vector4.hpp>
#include <Graphics/EffectParameter.hpp>
#include <Graphics/EffectParameterClass.hpp>
#include <Graphics/EffectParameterCollection.hpp>
#include <Graphics/EffectParameterType.hpp>
#include <Graphics/GraphicsDevice.hpp>
#include <Graphics/SamplerState.hpp>
#include <Graphics/SkinnedEffect.hpp>
#include <Graphics/TextureTarget.hpp>
#include <System/IO/File.hpp>
#include <cassert>

using namespace System;
using namespace System::IO;
using namespace SceneR::Framework;
using namespace SceneR::Graphics;

String SkinnedEffect::VSSource = File::ReadAllText(u"/home/carlos/development/projects/cpp/opengl/workspace/SceneR/Content/SkinnedEffect_VS.glsl");
String SkinnedEffect::FSSource = File::ReadAllText(u"/home/carlos/development/projects/cpp/opengl/workspace/SceneR/Content/SkinnedEffect_FS.glsl");

SkinnedEffect::SkinnedEffect(GraphicsDevice& graphicsDevice)
    : Effect(graphicsDevice, SkinnedEffect::VSSource, SkinnedEffect::FSSource),
      alpha(1.0),
      ambientLightColor(Vector3::Zero),
      boneTransforms(0),
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
      view(Matrix::Identity),
      weightsPerVertex(2),
      world(Matrix::Identity)
{
    this->Initialize();
}

SkinnedEffect::SkinnedEffect(const SkinnedEffect& effect)
    : Effect(effect),
      alpha(effect.alpha),
      ambientLightColor(effect.ambientLightColor),
      boneTransforms(effect.boneTransforms),
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
      view(effect.view),
      weightsPerVertex(effect.weightsPerVertex),
      world(effect.world)
{
    this->Initialize();
}

SkinnedEffect::~SkinnedEffect()
{
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

const std::shared_ptr<DirectionalLight>& SkinnedEffect::DirectionalLight0() const
{
    return this->directionalLight0;
}

void SkinnedEffect::DirectionalLight0(const std::shared_ptr<DirectionalLight>& directionalLight)
{
    this->directionalLight0 = directionalLight;
}

const std::shared_ptr<DirectionalLight>& SkinnedEffect::DirectionalLight1() const
{
    return this->directionalLight1;
}

void SkinnedEffect::DirectionalLight1(const std::shared_ptr<DirectionalLight>& directionalLight)
{
    this->directionalLight1 = directionalLight;
}

const std::shared_ptr<DirectionalLight>& SkinnedEffect::DirectionalLight2() const
{
    return this->directionalLight2;
}

void SkinnedEffect::DirectionalLight2(const std::shared_ptr<DirectionalLight>& directionalLight)
{
    this->directionalLight2 = directionalLight;
}

void SkinnedEffect::EnableDefaultLighting()
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

std::shared_ptr<Texture2D> SkinnedEffect::Texture() const
{
    return this->texture;
}

void SkinnedEffect::Texture(std::shared_ptr<Texture2D> texture)
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

const std::vector<Matrix>& SkinnedEffect::GetBoneTransforms(const System::Int32& count) const
{
    return this->boneTransforms;
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
        this->texture->Activate();
        this->CurrentGraphicsDevice().SamplerStates()[0].OnApply(TextureTarget::Texture2D, this->texture->LevelCount());
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
    // this->Parameters()[u"FogVector"].SetValue(Vector4());
    this->Parameters()[u"SpecularColor"].SetValue(this->SpecularColor());
    this->Parameters()[u"SpecularPower"].SetValue(this->SpecularPower());

    if (this->textureEnabled)
    {
        this->Parameters()[u"Texture"].SetValue(*this->texture);
    }

    this->Parameters()[u"World"].SetValue(worldView);
    this->Parameters()[u"WorldInverseTranspose"].SetValue(worldInverseTranspose);
    this->Parameters()[u"WorldViewProj"].SetValueTranspose(worldViewProjection);
    this->Parameters()[u"WeightsPerVertex"].SetValue(this->weightsPerVertex);
    this->Parameters()[u"Bones"].SetValue(this->boneTransforms);
}

void SkinnedEffect::Initialize()
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
    // this->Parameters().Add(u"FogVector"             , EffectParameterClass::Vector, EffectParameterType::Single   , this->shaderProgram);
    this->Parameters().Add(u"SpecularColor"         , EffectParameterClass::Vector, EffectParameterType::Single   , this->shaderProgram);
    this->Parameters().Add(u"SpecularPower"         , EffectParameterClass::Scalar, EffectParameterType::Single   , this->shaderProgram);
    this->Parameters().Add(u"Texture"               , EffectParameterClass::Object, EffectParameterType::Texture2D, this->shaderProgram);
    this->Parameters().Add(u"World"                 , EffectParameterClass::Matrix, EffectParameterType::Single   , this->shaderProgram);
    this->Parameters().Add(u"WorldInverseTranspose" , EffectParameterClass::Matrix, EffectParameterType::Single   , this->shaderProgram);
    this->Parameters().Add(u"WorldViewProj"         , EffectParameterClass::Matrix, EffectParameterType::Single   , this->shaderProgram);
    this->Parameters().Add(u"WeightsPerVertex"      , EffectParameterClass::Scalar, EffectParameterType::Int32    , this->shaderProgram);
    this->Parameters().Add(u"Bones"                 , EffectParameterClass::Matrix, EffectParameterType::Single   , this->shaderProgram);
}
