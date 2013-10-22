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

#include <cmath>
#include <vector>
#include "CustomRenderer.hpp"
#include "Graphics/Model.hpp"

using namespace SceneR::Core;
using namespace SceneR::Content;
using namespace SceneR::Custom;
using namespace SceneR::Graphics;

CustomRenderer::CustomRenderer(const std::string& rootDirectory)
    : Renderer(rootDirectory),
      model(nullptr)
{
}

void CustomRenderer::Draw()
{
    float aspect = this->GetGraphicsDevice().GetViewport().AspectRatio();

    this->GetGraphicsDevice().Clear(Color::Black);

    Matrix view = Matrix::CreateLookAt(Vector3(0.0f, -15.0f, 5.0f), Vector3(0.0f, 0.0f, 3.0f), Vector3(0.0f, 0.0f, 1.0f));

    Matrix projection = Matrix::CreatePerspectiveFieldOfView(45.0f, aspect, 0.1f, 100.0f);

    this->model->Draw(Matrix::CreateRotationZ(90.0f)  * Matrix::CreateTranslation(-6.0f, 0.0f, 0.0f), view, projection);
    this->model->Draw(Matrix::CreateRotationZ(0.0f)   * Matrix::CreateTranslation(-2.0f, 0.0f, 0.0f), view, projection);
    this->model->Draw(Matrix::CreateRotationZ(180.0f) * Matrix::CreateTranslation(2.0f, 0.0f, 0.0f), view, projection);
    this->model->Draw(Matrix::CreateRotationZ(-90.0f) * Matrix::CreateTranslation(6.0f, 0.0f, 0.0f), view, projection);
}

void CustomRenderer::Initialize()
{
    PresentationParameters& parameters = this->GetGraphicsDevice().GetPresentationParameters();

    parameters.SetBackBufferWidth(1500);
    parameters.SetBackBufferHeight(943);

    this->GetRendererWindow().SetTitle(L"SceneR");

    Renderer::Initialize();
}

void CustomRenderer::LoadContent()
{
    this->model = this->GetContentManager().Load<Model>("AstroBoy/astroBoy_walk_Max");

    Renderer::LoadContent();
}