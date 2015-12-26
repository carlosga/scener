// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <SampleRenderer.hpp>

#include <Framework/GraphicsDeviceManager.hpp>

#include <Camera.hpp>
#include <EarthShaker.hpp>

namespace SceneR
{
    namespace Sample
    {
        using SceneR::Framework::Color;
        using SceneR::Framework::RenderTime;

        SampleRenderer::SampleRenderer()
            : Renderer("/home/carlos/development/projects/cpp/opengl/scener/SceneR/Content")
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

        void SampleRenderer::draw(const RenderTime &renderTime)
        {
            graphics_device()->clear(Color::black);

            Renderer::draw(renderTime);
        }
    }
}
