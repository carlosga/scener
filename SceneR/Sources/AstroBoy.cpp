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

#include <AstroBoy.hpp>
#include <Content/ContentManager.hpp>
#include <Framework/Color.hpp>
#include <Framework/Matrix.hpp>
#include <Framework/Renderer.hpp>
#include <Framework/RenderTime.hpp>
#include <Framework/Vector3.hpp>
#include <Graphics/GraphicsDevice.hpp>
#include <Graphics/Model.hpp>
#include <Graphics/Viewport.hpp>

using namespace SceneR::Sample;
using namespace SceneR::Framework;
using namespace SceneR::Graphics;

AstroBoy::AstroBoy(SceneR::Framework::Renderer& renderer)
    : DrawableComponent(renderer)
{
}

AstroBoy::~AstroBoy()
{
    this->UnloadContent();
}

void AstroBoy::Draw(const RenderTime& renderTime)
{
    float aspect = this->CurrentGraphicsDevice().Viewport().AspectRatio();

    this->CurrentGraphicsDevice().Clear(Color::Black);

    Matrix view       = Matrix::CreateLookAt(Vector3(0.0f, 15.0f, 0.0f), Vector3(0.0f, 0.0f, 5.0f), Vector3(0.0f, 1.0f, 0.0f));
    Matrix projection = Matrix::CreatePerspectiveFieldOfView(45.0f, aspect, 1.0f, 100.0f);

    this->model->Draw(Matrix::CreateRotationZ(-90.0f) * Matrix::CreateTranslation(-6.0f, 0.0f, 0.0f), view, projection);
    this->model->Draw(Matrix::CreateRotationZ(0.0f)   * Matrix::CreateTranslation(-2.0f, 0.0f, 0.0f), view, projection);
    this->model->Draw(Matrix::CreateRotationZ(180.0f) * Matrix::CreateTranslation(2.0f, 0.0f, 0.0f) , view, projection);
    this->model->Draw(Matrix::CreateRotationZ(90.0f)  * Matrix::CreateTranslation(6.0f, 0.0f, 0.0f) , view, projection);
}

void AstroBoy::LoadContent()
{
    this->model = this->renderer.Content().Load<Model>(u"AstroBoy/astroBoy_walk_Max");
}

void AstroBoy::UnloadContent()
{
    if (this->model != nullptr)
    {
        this->model.reset();
        this->model = nullptr;
    }
}
