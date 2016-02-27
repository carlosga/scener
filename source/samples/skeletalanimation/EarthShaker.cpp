// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "skeletalanimation/EarthShaker.hpp"

#include <scener/content/content_manager.hpp>
#include <scener/graphics/effect_technique.hpp>
#include <scener/graphics/model.hpp>
#include <scener/graphics/model_mesh.hpp>
#include <scener/graphics/steptime.hpp>
#include <scener/math/basic_math.hpp>
#include <scener/math/vector.hpp>

#include "skeletalanimation/SampleRenderer.hpp"
#include "skeletalanimation/Camera.hpp"

namespace skeletal_animation {

using scener::graphics::model;
using scener::graphics::effect_technique;
using scener::graphics::steptime;
using scener::math::matrix4;

EarthShaker::EarthShaker(SampleRenderer* renderer) noexcept
    : drawable_component { renderer }
    , _model            { nullptr }
    , _world            { matrix4::identity() }
{
}

void EarthShaker::initialize() noexcept
{
    _world = scener::math::matrix::create_rotation_x({ -scener::math::pi_over_2<> })
           * scener::math::matrix::create_translation({ 0.0f, -70.0f, 0.0f });

    drawable_component::initialize();
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
    _world = matrix4::identity();
    _model = nullptr;
}

void EarthShaker::update(const steptime& renderTime) noexcept
{
    _model->update(renderTime);
}

void EarthShaker::draw(const steptime& renderTime) noexcept
{
    const auto camera = std::dynamic_pointer_cast<Camera>(_renderer->components()[0]);

    _model->draw(_world, camera->view, camera->projection);
}

}
