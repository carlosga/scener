// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "skeletal-animation/sample_renderer.hpp"

#include <scener/graphics/graphics_device.hpp>
#include <scener/graphics/graphics_device_manager.hpp>
#include <scener/math/color.hpp>

#include "skeletal-animation/camera.hpp"
#include "skeletal-animation/earthshaker.hpp"

namespace skeletal { namespace animation {

using scener::graphics::steptime;
using scener::math::color;

sample_renderer::sample_renderer() noexcept
    : renderer("./content")
{
}

void sample_renderer::begin_run() noexcept
{
    renderer::begin_run();

    device_manager()->preferred_back_buffer_width  = 1600;
    device_manager()->preferred_back_buffer_height = 900;
    device_manager()->window_title                 = "SceneR";
}

void sample_renderer::load_content() noexcept
{
    renderer::load_content();

    add_component(std::make_shared<camera>(this));
    add_component(std::make_shared<earthshaker>(this));
}

void sample_renderer::draw(const steptime& time) noexcept
{
    device()->clear(color::black());

    renderer::draw(time);
}

}}
