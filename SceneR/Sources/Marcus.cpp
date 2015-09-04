// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Marcus.hpp>

#include <Camera.hpp>
#include <SampleRenderer.hpp>

#include <System/Math.hpp>
#include <Framework/RenderTime.hpp>
#include <Framework/Vector3.hpp>
#include <Graphics/Model.hpp>
#include <Graphics/ModelMesh.hpp>

namespace SceneR
{
    namespace Sample
    {
        using System::Math;
        using SceneR::Framework::Matrix;
        using SceneR::Framework::RenderTime;
        using SceneR::Graphics::Model;
        using SceneR::Graphics::SkinnedEffect;

        Marcus::Marcus(SampleRenderer& renderer)
            : DrawableComponent { renderer }
            , model             { nullptr }
            , world             { Matrix::Identity }
        {
        }

        void Marcus::Initialize()
        {
            this->world = Matrix::CreateRotationX(-Math::PiOver2)
                        * Matrix::CreateTranslation({ 0.0f, -40.0f, 0.0f })
                        * Matrix::CreateScale(2.0f);

            DrawableComponent::Initialize();
        }

        void Marcus::LoadContent()
        {
//            this->model         = this->renderer.content_manager().Load<Model>(u"Marcus/marcus");
//
//            for (const auto& mesh : this->model->Meshes())
//            {
//                for (auto& effect : mesh->Effects())
//                {
//                    auto seffect = std::dynamic_pointer_cast<SkinnedEffect>(effect);
//
//                    if (seffect.get() != nullptr)
//                    {
//                        seffect->enable_default_lighting();
//                        seffect->SpecularColor({ 0.15f, 0.15f, 0.15f });
//                        seffect->PreferPerPixelLighting(true);
//                    }
//                }
//            }
//
//            // Start default animation clip
//            this->animatedModel->PlayFirstClip();
        }

        void Marcus::UnloadContent()
        {
            this->world = Matrix::Identity;
            this->model = nullptr;
        }

        void Marcus::Update(const RenderTime& renderTime)
        {
            // this->model->update(renderTime);
        }

        void Marcus::Draw(const RenderTime& renderTime)
        {
            const auto camera = std::dynamic_pointer_cast<Camera>(this->renderer.components()[0]);

            this->model->draw(this->world, camera->View, camera->Projection);
        }
    }
}
