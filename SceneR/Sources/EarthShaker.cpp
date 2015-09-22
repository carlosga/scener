// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "EarthShaker.hpp"

#include <Camera.hpp>
#include <SampleRenderer.hpp>

#include <Content/ContentManager.hpp>
#include <Framework/RenderTime.hpp>
#include <Framework/Vector3.hpp>
#include <Graphics/EffectTechnique.hpp>
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
        using SceneR::Graphics::EffectTechnique;
        using System::Math;

        EarthShaker::EarthShaker(SampleRenderer* renderer)
            : DrawableComponent { renderer }
            , _model            { nullptr }
            , _world            { Matrix::identity }
        {
        }

        void EarthShaker::initialize()
        {
            _world = Matrix::create_translation({ 0.0f, -70.0f, 0.0f });

            DrawableComponent::initialize();
        }

        void EarthShaker::load_content()
        {
            _model = _renderer->content_manager()->load("earthshaker/earthshaker");

            for (auto mesh : _model->meshes())
            {
                for (auto effect : mesh->effects())
                {
                    effect->texture_enabled(true);
                }
            }
//
//            // Start default animation clip
//            this->animatedModel->PlayFirstClip();
        }

        void EarthShaker::unload_content()
        {
            _world = Matrix::identity;
            _model = nullptr;
        }

        void EarthShaker::update(const RenderTime& renderTime)
        {
            // this->model->update(renderTime);
        }

        void EarthShaker::draw(const RenderTime& renderTime)
        {
            const auto camera = std::dynamic_pointer_cast<Camera>(_renderer->components()[0]);

            _model->draw(_world, camera->view, camera->projection);
        }
    }
}
