// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Marcus.hpp>

#include <Camera.hpp>
#include <SampleRenderer.hpp>

#include <Framework/RenderTime.hpp>
#include <Framework/Vector3.hpp>
#include <Graphics/Model.hpp>
#include <Graphics/ModelMesh.hpp>
#include <System/Math.hpp>

namespace SceneR
{
    namespace Sample
    {
        using SceneR::Framework::Matrix;
        using SceneR::Framework::RenderTime;
        using SceneR::Graphics::Model;
        using SceneR::Graphics::SkinnedEffect;
        using System::Math;

        Marcus::Marcus(SampleRenderer& renderer)
            : DrawableComponent { renderer }
            , _model            { nullptr }
            , _world            { Matrix::identity }
        {
        }

        void Marcus::initialize()
        {
            _world = Matrix::create_rotation_x(-Math::pi_over_2)
                   * Matrix::create_translation({ 0.0f, -40.0f, 0.0f })
                   * Matrix::create_scale(2.0f);

            DrawableComponent::initialize();
        }

        void Marcus::load_content()
        {
            _model = _renderer.content_manager().load_model(u"marcus/marcus");
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

        void Marcus::unload_content()
        {
            _world = Matrix::identity;
            _model = nullptr;
        }

        void Marcus::update(const RenderTime& renderTime)
        {
            // this->model->update(renderTime);
        }

        void Marcus::draw(const RenderTime& renderTime)
        {
            const auto camera = std::dynamic_pointer_cast<Camera>(_renderer.components()[0]);

            _model->draw(_world, camera->view, camera->projection);
        }
    }
}
