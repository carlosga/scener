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

#include <BumbleBee.hpp>
#include <Framework/MathHelper.hpp>
#include <Framework/RenderTime.hpp>
#include <Framework/Vector3.hpp>
#include <Graphics/Model.hpp>

using namespace System;
using namespace SceneR::Sample;
using namespace SceneR::Framework;
using namespace SceneR::Graphics;

BumbleBee::BumbleBee(SceneR::Framework::Renderer& renderer)
    : DrawableComponent(renderer),
      model(nullptr),
      rotation(0.0f),
      world(Matrix::Identity),
      view(Matrix::Identity),
      projection(Matrix::Identity)
{
}

BumbleBee::~BumbleBee()
{
    this->UnloadContent();
}

void BumbleBee::Update(const RenderTime& renderTime)
{
    Single aspect      = this->CurrentGraphicsDevice().Viewport().AspectRatio();
    Single newRotation = this->rotation + renderTime.ElapsedRenderTime().TotalSeconds();

    this->rotation   = MathHelper::SmoothStep(this->rotation, newRotation, MathHelper::PiOver4);
    this->world      = Matrix::CreateRotationX(-90.0f)
                     * Matrix::CreateRotationY(MathHelper::ToDegrees(this->rotation))
                     * Matrix::CreateTranslation(Vector3(-300.0f, -400.0f, 0.0f));
    this->view       = Matrix::CreateLookAt(Vector3(0.0f, 0.0f, 1200.0f), Vector3::Zero, Vector3::Up);
    this->projection = Matrix::CreatePerspectiveFieldOfView(MathHelper::PiOver4, aspect, 1.0f, 10000.0f);
}

void BumbleBee::Draw(const RenderTime& renderTime)
{
    this->model->Draw(this->world, this->view, this->projection);
}

void BumbleBee::LoadContent()
{
    this->model = this->renderer.Content().Load<Model>(u"BumbleBee/RB-BumbleBee");
}

void BumbleBee::UnloadContent()
{
    if (this->model != nullptr)
    {
        this->model.reset();
        this->model = nullptr;
    }
}
