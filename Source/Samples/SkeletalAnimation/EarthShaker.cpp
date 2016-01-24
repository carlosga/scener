// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SkeletalAnimation/EarthShaker.hpp"

#include <SceneR/Content/ContentManager.hpp>
#include <SceneR/Graphics/EffectTechnique.hpp>
#include <SceneR/Graphics/Model.hpp>
#include <SceneR/Graphics/ModelMesh.hpp>
#include <SceneR/Graphics/StepTime.hpp>
#include <SceneR/Math/Math.hpp>
#include <SceneR/Math/Vector3.hpp>

#include "SkeletalAnimation/SampleRenderer.hpp"
#include "SkeletalAnimation/Camera.hpp"

namespace SkeletalAnimation {

using SceneR::Graphics::Model;
using SceneR::Graphics::EffectTechnique;
using SceneR::Graphics::StepTime;
using SceneR::Math::Matrix;

EarthShaker::EarthShaker(SampleRenderer* renderer) noexcept
    : DrawableComponent { renderer }
    , _model            { nullptr }
    , _world            { Matrix::identity }
{
}

void EarthShaker::initialize() noexcept
{
    _world = Matrix::create_rotation_x({ -SceneR::Math::pi_over_2 })
           * Matrix::create_translation({ 0.0f, -70.0f, 0.0f });

    DrawableComponent::initialize();
}

void EarthShaker::load_content() noexcept
{
    _model = _renderer->content_manager()->load("earthshaker/earthshaker");

    for (const auto& mesh : _model->meshes())
    {
        for (const auto& effect : mesh->effects())
        {
            effect->texture_enabled(true);
        }
    }
}

void EarthShaker::unload_content() noexcept
{
    _world = Matrix::identity;
    _model = nullptr;
}

void EarthShaker::update(const StepTime& renderTime) noexcept
{
    _model->update(renderTime);
}

void EarthShaker::draw(const StepTime& renderTime) noexcept
{
    const auto camera = std::dynamic_pointer_cast<Camera>(_renderer->components()[0]);

    _model->draw(_world, camera->view, camera->projection);
}

}
