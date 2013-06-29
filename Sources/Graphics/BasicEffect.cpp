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

#include <memory>
#include <stdexcept>
#include <vector>
#include "Graphics/BasicEffect.hpp"
#include "IO/File.hpp"
#include "Shaders/Shader.hpp"
#include "Shaders/ShaderProgram.hpp"
#include "Shaders/ShaderType.hpp"

using namespace SceneR::Core;
using namespace SceneR::Graphics;
using namespace SceneR::IO;
using namespace SceneR::Shaders;

BasicEffect::BasicEffect(GraphicsDevice& graphicsDevice)
    : Effect(graphicsDevice),
      alpha(0),
      ambientLight(),
      diffuseColor(0, 0, 0, 1),
      lights(0),
      lightingEnabled(true),
      emissiveColor(0, 0, 0, 1),
      fogEnabled(false),
      fogColor(0, 0, 0, 1),
      fogEnd(0),
      fogStart(0),
      preferPerPixelLighting(false),
      projection(Matrix::Identity),
      specularColor(0, 0, 0, 1),
      specularPower(0),
      textureEnabled(true),
      texture(nullptr),
      vertexColorEnabled(false),
      view(Matrix::Identity),
      world(Matrix::Identity)
{
    this->LoadShader();
}

const Single& BasicEffect::GetAlpha() const
{
    return this->alpha;
}

void BasicEffect::SetAlpha(const Single& alpha)
{
    this->alpha = alpha;
}

const AmbientLight& BasicEffect::GetAmbientLight() const
{
    return this->ambientLight;
}

void BasicEffect::SetAmbientLight(const AmbientLight& ambientLight)
{
    this->ambientLight = ambientLight;
}

const Color& BasicEffect::GetDiffuseColor() const
{
    return this->diffuseColor;
}

void BasicEffect::SetDiffuseColor(Color& diffuseColor)
{
    this->diffuseColor = diffuseColor;
}

const std::vector<std::shared_ptr<Light>>& BasicEffect::GetLights() const
{
    return this->lights;
}

void BasicEffect::SetLights(const std::vector<std::shared_ptr<Light>> lights) const
{
    throw std::runtime_error("Not implemented");
    // this->lights = lights;
}

const Color& BasicEffect::GetEmissiveColor() const
{
    return this->emissiveColor;
}

void BasicEffect::SetEmissiveColor(Color& emissiveColor)
{
    this->emissiveColor = emissiveColor;
}

const Color& BasicEffect::GetFogColor() const
{
    return this->fogColor;
}

void BasicEffect::SetFogColor(const Color& fogColor)
{
    this->fogColor = fogColor;
}

void BasicEffect::EnableFog()
{
    this->fogEnabled = true;
}

void BasicEffect::DisableFog()
{
    this->fogEnabled = false;
}

const Boolean& BasicEffect::IsFogEnabled() const
{
    return this->fogEnabled;
}

const Single& BasicEffect::GetFogEnd() const
{
    return this->fogEnd;
}

void BasicEffect::SetFogEnd(const Single& fogEnd)
{
    this->fogEnd = fogEnd;
}

const Single& BasicEffect::GetFogStart() const
{
    return this->fogStart;
}

void BasicEffect::SetFogStart(const Single& fogStart)
{
    this->fogStart = fogStart;
}

void BasicEffect::EnableLighting()
{
    this->lightingEnabled = true;
}

void BasicEffect::DisableLighting()
{
    this->lightingEnabled = false;
}

const Boolean& BasicEffect::IsLightingEnabled()
{
    return this->lightingEnabled;
}

const Boolean& BasicEffect::GetPreferPerPixelLighting() const
{
    return this->preferPerPixelLighting;
}

void BasicEffect::SetPreferPerPixelLighting(const Boolean& preferPerPixelLighting)
{
    this->preferPerPixelLighting = preferPerPixelLighting;
}

const Matrix& BasicEffect::GetProjection() const
{
    return this->projection;
}

void BasicEffect::SetProjection(const Matrix& projection)
{
    this->projection = projection;
}

const Color& BasicEffect::GetSpecularColor() const
{
    return this->specularColor;
}

void BasicEffect::SetSpecularColor(const Color& specularColor)
{
    this->specularColor = specularColor;
}

const Single& BasicEffect::GetSpecularPower() const
{
    return this->specularPower;
}

void BasicEffect::SetSpecularPower(const Single& specularPower)
{
    this->specularPower = specularPower;
}

std::shared_ptr<Texture2D> BasicEffect::GetTexture() const
{
    return this->texture;
}

void BasicEffect::SetTexture(std::shared_ptr<Texture2D> texture)
{
    this->texture = texture;
}

void BasicEffect::EnableTexture()
{
    this->textureEnabled = true;
}

void BasicEffect::DisableTexture()
{
    this->textureEnabled = false;
}

const Boolean& BasicEffect::IsTextureEnabled() const
{
    return this->textureEnabled;
}

const Matrix& BasicEffect::GetView() const
{
    return this->view;
}

void BasicEffect::SetView(const Matrix& view)
{
    this->view = view;
}

void BasicEffect::EnableVertexColor()
{
    this->vertexColorEnabled = true;
}

void BasicEffect::DisableVertexColor()
{
    this->vertexColorEnabled = false;
}

const Boolean& BasicEffect::IsVertexColorEnabled() const
{
    return this->vertexColorEnabled;
}

const Matrix& BasicEffect::GetWorld() const
{
    return this->world;
}

void BasicEffect::SetWorld(const Matrix& world)
{
    this->world = world;
}

void BasicEffect::EnableDefaultLighting()
{
    /*
    http://xboxforums.create.msdn.com/forums/t/25547.aspx
    
    effect.LightingEnabled = true;

    effect.AmbientLightColor = new Vector3(0.053f, 0.098f, 0.181f);
    effect.SpecularColor = new Vector3(0, 0, 0);
    effect.DiffuseColor = new Vector3(0.64f, 0.64f, 0.64f);

    effect.DirectionalLight0.Enabled = true;
    effect.DirectionalLight0.DiffuseColor = new Vector3(1f, 0.96f, 0.81f);
    effect.DirectionalLight0.Direction = new Vector3(-0.52f, -0.57f, -0.62f);
    effect.DirectionalLight0.SpecularColor = new Vector3(1f, 0.96f, 0.81f);

    effect.DirectionalLight1.Enabled = true;
    effect.DirectionalLight1.DiffuseColor = new Vector3(0.96f, 0.76f, 0.40f);
    effect.DirectionalLight1.Direction = new Vector3(0.71f, 0.34f, 0.60f);
    effect.DirectionalLight1.SpecularColor = new Vector3(0f, 0f, 0f);

    effect.DirectionalLight2.Enabled = true;
    effect.DirectionalLight2.DiffuseColor = new Vector3(0.32f, 0.36f, 0.39f);
    effect.DirectionalLight2.Direction = new Vector3(0.45f, -0.76f, 0.45f);
    effect.DirectionalLight2.SpecularColor = new Vector3(0.32f, 0.36f, 0.39f);
    */
}

void BasicEffect::OnApply()
{
    Matrix worldInverseTranspose(this->world);

    worldInverseTranspose.Invert();
    worldInverseTranspose.Transpose();

    Effect::GetEffectParameter(L"WorldView").SetValue(this->world * this->view);
    Effect::GetEffectParameter(L"WorldViewProjection").SetValue(this->world * this->view * this->projection);
    Effect::GetEffectParameter(L"WorldInverseTranspose").SetValue(worldInverseTranspose);
    Effect::GetEffectParameter(L"LightPosition").SetValue(Vector4(5.0f, -5.0, -5.0f, 1.0f));
    Effect::GetEffectParameter(L"LightIntensity").SetValue(Vector3(0.52f , 0.57f , 0.62f));
    Effect::GetEffectParameter(L"Ka").SetValue(Vector3(0.053f, 0.098f, 0.181f));
    Effect::GetEffectParameter(L"Kd").SetValue(Vector3(0.64f , 0.64f , 0.64f));
    Effect::GetEffectParameter(L"Ks").SetValue(Vector3(0.32f , 0.36f , 0.39f));
    Effect::GetEffectParameter(L"Shininess").SetValue(1.0f);
}

void BasicEffect::LoadShader()
{
    // TODO: Check how to resolve the content manager here to build the shader pipeline from disk
    // TODO: Use EffectParameters and get parameter locations only once
    std::wstring            vSource = File::ReadAllText("/home/carlos/development/projects/cpp/opengl/workspace/SceneR/Content/BasicEffect_VS.glsl");
    std::wstring            fSource = File::ReadAllText("/home/carlos/development/projects/cpp/opengl/workspace/SceneR/Content/BasicEffect_FS.glsl");
    std::shared_ptr<Shader> vShader = std::make_shared<Shader>(vSource, ShaderType::Vertex);
    std::shared_ptr<Shader> fShader = std::make_shared<Shader>(fSource, ShaderType::Fragment);

    std::vector<std::shared_ptr<Shader>> shaders;

    shaders.push_back(vShader);
    shaders.push_back(fShader);

    this->shaderProgram = std::make_shared<ShaderProgram>(L"BasicEffect", shaders);
    this->shaderProgram->Build();
    
    Effect::AddEffectParameter(L"WorldView"             , EffectParameterClass::Matrix, EffectParameterType::Single);
    Effect::AddEffectParameter(L"WorldViewProjection"   , EffectParameterClass::Matrix, EffectParameterType::Single);
    Effect::AddEffectParameter(L"WorldInverseTranspose" , EffectParameterClass::Matrix, EffectParameterType::Single);
    Effect::AddEffectParameter(L"LightPosition"         , EffectParameterClass::Vector, EffectParameterType::Single);
    Effect::AddEffectParameter(L"LightIntensity"        , EffectParameterClass::Vector, EffectParameterType::Single);
    Effect::AddEffectParameter(L"Ka"                    , EffectParameterClass::Vector, EffectParameterType::Single);
    Effect::AddEffectParameter(L"Kd"                    , EffectParameterClass::Vector, EffectParameterType::Single);
    Effect::AddEffectParameter(L"Ks"                    , EffectParameterClass::Vector, EffectParameterType::Single);
    Effect::AddEffectParameter(L"Shininess"             , EffectParameterClass::Scalar, EffectParameterType::Single);
}
