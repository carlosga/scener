// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "skeletalanimation/SampleRenderer.hpp"

#include <scener/graphics/GraphicsDevice.hpp>
#include <scener/graphics/GraphicsDeviceManager.hpp>
#include <scener/math/Color.hpp>

#include "skeletalanimation/Camera.hpp"
#include "skeletalanimation/EarthShaker.hpp"

namespace skeletal_animation {

using scener::graphics::steptime;
using scener::math::Color;

SampleRenderer::SampleRenderer() noexcept
    : renderer("./content")
{
}

void SampleRenderer::begin_run() noexcept
{
    renderer::begin_run();

    device_manager()->preferred_back_buffer_width  = 1600;
    device_manager()->preferred_back_buffer_height = 900;
    device_manager()->window_title                 = "SceneR";
}

void SampleRenderer::load_content() noexcept
{
    renderer::load_content();

    add_component(std::make_shared<Camera>(this));
    add_component(std::make_shared<EarthShaker>(this));
}

void SampleRenderer::draw(const steptime& time) noexcept
{
    device()->clear(Color::black);

    renderer::draw(time);
}

}
