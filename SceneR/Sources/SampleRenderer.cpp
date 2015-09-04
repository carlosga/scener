// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <SampleRenderer.hpp>

#include <Camera.hpp>
#include <Marcus.hpp>

namespace SceneR
{
    namespace Sample
    {
        using SceneR::Framework::Color;
        using SceneR::Framework::RenderTime;

        SampleRenderer::SampleRenderer()
            : Renderer(u"/home/carlos/development/projects/cpp/opengl/scener/SceneR/content_manager/")
        {
        }

        void SampleRenderer::begin_run()
        {
            _graphics_device_manager.preferred_back_buffer_width  = 1600;
            _graphics_device_manager.preferred_back_buffer_height = 900;
            _graphics_device_manager.window_title                 = u"SceneR";

            this->components().push_back(std::make_shared<Camera>(*this));
            this->components().push_back(std::make_shared<Marcus>(*this));

            Renderer::begin_run();
        }

        void SampleRenderer::draw(const RenderTime &renderTime)
        {
            _graphics_device_manager.graphics_device().clear(Color::Black);

            Renderer::draw(renderTime);
        }
    }
}
