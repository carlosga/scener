// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "skeletal-animation/earthshaker.hpp"

#include <scener/content/content_manager.hpp>
#include <scener/graphics/effect_technique.hpp>
#include <scener/graphics/model.hpp>
#include <scener/graphics/model_mesh.hpp>
#include <scener/graphics/steptime.hpp>
#include <scener/math/basic_math.hpp>
#include <scener/math/vector.hpp>

#include "skeletal-animation/sample_renderer.hpp"
#include "skeletal-animation/camera.hpp"

namespace skeletal::animation
{
    using scener::graphics::model;
    using scener::graphics::effect_technique;
    using scener::graphics::steptime;
    using scener::math::matrix4;
    using scener::math::matrix::create_rotation_x;
    using scener::math::matrix::create_translation;

    earthshaker::earthshaker(sample_renderer* renderer) noexcept
        : drawable_component { renderer }
        , _model             { nullptr }
        , _world             { matrix4::identity() }
    {
    }

    void earthshaker::initialize() noexcept
    {
        _world = create_rotation_x({ -scener::math::pi_over_2<> })
               * create_translation({ 0.0f, -70.0f, 0.0f });

        drawable_component::initialize();
    }

    void earthshaker::load_content() noexcept
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

    void earthshaker::unload_content() noexcept
    {
        _world = matrix4::identity();
        _model = nullptr;
    }

    void earthshaker::update(const steptime& time) noexcept
    {
        _model->update(time);
    }

    void earthshaker::draw([[maybe_unused]] const steptime& time) noexcept
    {
        const auto camera_component = std::dynamic_pointer_cast<camera>(_renderer->components()[0]);

        _model->draw(_world, camera_component->view, camera_component->projection);
    }
}
