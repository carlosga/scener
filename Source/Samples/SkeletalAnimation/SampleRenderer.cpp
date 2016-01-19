// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SkeletalAnimation/SampleRenderer.hpp"

#include <SceneR/Graphics/GraphicsDevice.hpp>
#include <SceneR/Graphics/GraphicsDeviceManager.hpp>
#include <SceneR/Math/Color.hpp>

#include "SkeletalAnimation/Camera.hpp"
#include "SkeletalAnimation/EarthShaker.hpp"

namespace SkeletalAnimation {

using SceneR::Graphics::StepTime;
using SceneR::Math::Color;

SampleRenderer::SampleRenderer() noexcept
    : Renderer("./Content")
{
}

void SampleRenderer::begin_run() noexcept
{
    Renderer::begin_run();

    graphics_device_manager()->preferred_back_buffer_width  = 1600;
    graphics_device_manager()->preferred_back_buffer_height = 900;
    graphics_device_manager()->window_title                 = "SceneR";
}

void SampleRenderer::load_content() noexcept
{
    Renderer::load_content();

    add_component(std::make_shared<Camera>(this));
    add_component(std::make_shared<EarthShaker>(this));
}

void SampleRenderer::draw(const StepTime &renderTime) noexcept
{
    graphics_device()->clear(Color::black);

    Renderer::draw(renderTime);
}

}
