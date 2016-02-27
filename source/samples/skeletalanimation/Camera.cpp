// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "skeletalanimation/Camera.hpp"

#include <scener/graphics/graphics_device.hpp>
#include <scener/graphics/window.hpp>
#include <scener/input/keys.hpp>
#include <scener/input/keyboard.hpp>
#include <scener/input/keyboard_state.hpp>

#include "skeletalanimation/SampleRenderer.hpp"

namespace skeletal_animation {

using scener::graphics::steptime;
using scener::input::keys;
using scener::input::keyboard;
using scener::input::keyboard_state;
using scener::math::degrees;
using scener::math::radians;
using scener::math::matrix4;
using scener::math::vector3;

camera::camera(sample_renderer* renderer) noexcept
    : component           { renderer }
    , view                { matrix4::identity() }
    , projection          { matrix4::identity() }
    , _position           { }
    , _rotation_transform { }
    , _rotation           { 0.0f }
    , _resize_connection  { }
{
}

void camera::initialize() noexcept
{
    _position           = { 0.0f, 0.0f, 500.0f };
    _rotation           = 0.0f;
    _rotation_transform = matrix4::identity();

    update_projection();

    _resize_connection = _renderer->window()->connect_resize([&](std::uint32_t, std::uint32_t) {
        update_projection();
    });
}

void camera::update(const steptime& time) noexcept
{
    auto keyboard_state   = keyboard::get_state();
    auto current_position = _position;
    auto new_position     = _position;
    auto current_rotation = _rotation;
    auto new_rotation     = _rotation;

    if (keyboard_state.is_key_down(keys::D))
    {
        new_position += { 1.0f, 0.0f, 0.0f };
    }
    if (keyboard_state.is_key_down(keys::A))
    {
        new_position += { -1.0f, 0.0f, 0.0f };
    }
    if (keyboard_state.is_key_down(keys::W))
    {
        new_position += { 0.0f, 0.0f, 1.0f };
    }
    if (keyboard_state.is_key_down(keys::S))
    {
        new_position += { 0.0f, 0.0f, -1.0f };
    }
    if (keyboard_state.is_key_down(keys::Z))
    {
        new_position += { 0.0f, 1.0f, 0.0f };
    }
    if (keyboard_state.is_key_down(keys::C))
    {
        new_position += { 0.0f, -1.0f, 0.0f };
    }

    if (keyboard_state.is_key_down(keys::Q))
    {
        new_rotation = current_rotation + time.elapsed_render_time.total_seconds();
    }
    if (keyboard_state.is_key_down(keys::E))
    {
        new_rotation = current_rotation - time.elapsed_render_time.total_seconds();
    }

    if (current_rotation != new_rotation)
    {
        _rotation = scener::math::smooth_step(current_rotation.value, new_rotation.value, scener::math::pi_over_2<>);
    }

    if (current_rotation != _rotation)
    {
        _rotation_transform = scener::math::matrix::create_rotation_y(radians(_rotation), vector3::zero());
    }

    _position = scener::math::vector::lerp(current_position, new_position, scener::math::pi_over_2<>);

    view = _rotation_transform * scener::math::matrix::create_look_at(_position, vector3::zero(), vector3::up());
}

void camera::update_projection() noexcept
{
    static const radians fov = degrees(45.0f);

    auto aspect = _renderer->device()->viewport().aspect_ratio();

    projection = scener::math::matrix::create_perspective_field_of_view(fov, aspect, 0.1f, 1000.0f);
    view       = scener::math::matrix::create_look_at(_position, vector3::zero(), vector3::up());
}

}
