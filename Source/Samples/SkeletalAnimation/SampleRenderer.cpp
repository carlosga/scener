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

SampleRenderer::SampleRenderer()
    : Renderer("./Content")
{
}

void SampleRenderer::begin_run()
{
    Renderer::begin_run();

    _graphics_device_manager->preferred_back_buffer_width  = 1600;
    _graphics_device_manager->preferred_back_buffer_height = 900;
    _graphics_device_manager->window_title                 = "SceneR";
}

void SampleRenderer::load_content()
{
    Renderer::load_content();

    Renderer::_components.push_back(std::make_shared<Camera>(this));
    Renderer::_components.push_back(std::make_shared<EarthShaker>(this));
}

void SampleRenderer::draw(const StepTime &renderTime)
{
    graphics_device()->clear(Color::black);

    Renderer::draw(renderTime);
}

}
