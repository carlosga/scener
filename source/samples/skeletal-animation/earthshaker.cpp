// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "skeletal-animation/earthshaker.hpp"

#include <scener/content/content_manager.hpp>
#include <scener/graphics/model.hpp>
#include <scener/graphics/model_mesh.hpp>
#include <scener/graphics/model_mesh_part.hpp>
#include <scener/graphics/window.hpp>
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
    using scener::math::matrix::create_rotation_z;
    using scener::math::matrix::create_translation;
    using scener::math::matrix::create_scale;

    earthshaker::earthshaker(sample_renderer* renderer) noexcept
        : drawable_component { renderer }
        , _model             { nullptr }
        , _world             { matrix4::identity() }
    {
    }

    void earthshaker::initialize() noexcept
    {
        _world = create_rotation_z({ -scener::math::pi_over_2<> })
               * create_translation({ 0.0f, 0.0f, -150.0f });

        drawable_component::initialize();
    }

    void earthshaker::load_content() noexcept
    {
        _model = _renderer->content_manager()->load("earthshaker/earthshaker");

        std::for_each(_model->meshes().begin(), _model->meshes().end(), [] (auto mesh) -> void
        {
            std::for_each(mesh->mesh_parts().begin(), mesh->mesh_parts().end(), [] (auto part) -> void
            {
                part->effect_technique()->texture_enabled(true);
            });
        });
    }

    void earthshaker::unload_content() noexcept
    {
        _world = matrix4::identity();
        _model = nullptr;
    }

    void earthshaker::update(const steptime& time) noexcept
    {
        const auto camera_component = std::dynamic_pointer_cast<camera>(_renderer->components()[0]);

        _model->update(time, _world, camera_component->view, camera_component->projection);
    }

    void earthshaker::draw() noexcept
    {
        _model->draw();
    }
}
