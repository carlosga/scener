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

#include <Content/ContentManager.hpp>
#include <Framework/MathHelper.hpp>
#include <Framework/RenderTime.hpp>
#include <Framework/Vector3.hpp>
#include <Graphics/GraphicsDevice.hpp>
#include <Graphics/Viewport.hpp>
#include <Marcus.hpp>
#include <System/TimeSpan.hpp>

using namespace System;
using namespace SceneR::Sample;
using namespace SceneR::Framework;
using namespace SceneR::Graphics;

Marcus::Marcus(SceneR::Framework::Renderer& renderer)
    : DrawableComponent(renderer),
      model(nullptr),
      animatedModel(nullptr),
      world(Matrix::Identity),
      view(Matrix::Identity),
      projection(Matrix::Identity)
{
}

Marcus::~Marcus()
{
    this->UnloadContent();
}

void Marcus::Update(const RenderTime& renderTime)
{
    Single aspect = this->CurrentGraphicsDevice().Viewport().AspectRatio();

    this->world      = Matrix::CreateRotationX(-MathHelper::PiOver2)
                     * Matrix::CreateRotationY(MathHelper::ToRadians(150.0f))
                     * Matrix::CreateTranslation(Vector3(0.0f, -40.0f, 100.0f));
    this->view       = Matrix::CreateLookAt(Vector3(0.0f, 0.0f, -10.0f), Vector3::Zero, Vector3::Up);
    this->projection = Matrix::CreatePerspectiveFieldOfView(MathHelper::PiOver4, aspect, 1.0f, 10000.0f);

    this->animatedModel->Update(renderTime);
}

void Marcus::Draw(const RenderTime& renderTime)
{
    this->animatedModel->Draw(this->world, this->view, this->projection);
}

void Marcus::LoadContent()
{
    this->model         = this->renderer.Content().Load<Model>(u"Marcus/marcus");
    this->animatedModel = std::make_shared<AnimatedModel>(this->model);

    // Start default animation clip
    this->animatedModel->PlayFirstClip();
}

void Marcus::UnloadContent()
{
    if (this->model != nullptr)
    {
        this->model.reset();
        this->model = nullptr;
    }
}
