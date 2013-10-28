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
#include <Framework/Renderer.hpp>
#include <Graphics/Model.hpp>

using namespace SceneR::Sample;
using namespace SceneR::Framework;
using namespace SceneR::Graphics;

AstroBoy::AstroBoy(Renderer& renderer)
    : DrawableComponent(renderer)
{
}

AstroBoy::~AstroBoy()
{
    this->UnloadContent();
}

void AstroBoy::Draw()
{
    //this->model->Draw(Matrix::CreateRotationZ(90.0f)  * Matrix::CreateTranslation(-6.0f, 0.0f, 0.0f), view, projection);
    DrawableComponent::Draw();
}

void AstroBoy::LoadContent()
{
    //this->model = this->renderer.GetContentManager().Load<Model>("AstroBoy/astroBoy_walk_Max");
}

void AstroBoy::UnloadContent()
{
    if (this->model != nullptr)
    {
        this->model.reset();
        this->model = nullptr;
    }
}
