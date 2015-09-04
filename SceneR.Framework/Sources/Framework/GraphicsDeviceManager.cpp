// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Framework/GraphicsDeviceManager.hpp>

#include <Framework/PresentInterval.hpp>
#include <Graphics/GraphicsDevice.hpp>
#include <Graphics/GraphicsAdapter.hpp>
#include <Graphics/GraphicsProfile.hpp>
#include <Framework/Renderer.hpp>

namespace SceneR
{
    namespace Framework
    {
        using SceneR::Graphics::GraphicsAdapter;
        using SceneR::Graphics::GraphicsDevice;
        using SceneR::Graphics::GraphicsProfile;
        using SceneR::Graphics::IGraphicsDeviceService;

        GraphicsDeviceManager::GraphicsDeviceManager(Renderer& renderer)
            : allow_user_resizing          { false }
            , graphics_profile             { GraphicsProfile::HiDef }
            , window_title                 {  }
            , full_screen                  { false }
            , preferred_back_buffer_width  { 0 }
            , preferred_back_buffer_height { 0 }
            , _graphics_device             { nullptr }
            , _renderer                    { renderer }
        {
            _renderer.services().add_service<IGraphicsDeviceService>(*this);
        }

        GraphicsDeviceManager::~GraphicsDeviceManager()
        {
        }

        void GraphicsDeviceManager::dispose()
        {
            if (_graphics_device)
            {
                _graphics_device->dispose();
                _graphics_device = nullptr;
            }
        }

        void GraphicsDeviceManager::apply_changes()
        {
            _graphics_device->presentation_parameters().BackBufferWidth(preferred_back_buffer_width);
            _graphics_device->presentation_parameters().BackBufferHeight(preferred_back_buffer_height);
            _graphics_device->presentation_parameters().FullScreen(full_screen);

            _renderer.window().title(window_title);
            _renderer.window().allow_user_resizing(allow_user_resizing);

            _graphics_device->viewport().width  = preferred_back_buffer_width;
            _graphics_device->viewport().height = preferred_back_buffer_height;
            _graphics_device->viewport().update();

            _graphics_device->blend_state().Apply();
            _graphics_device->rasterizer_state().apply();
            _graphics_device->depth_stencil_state().Apply();

            switch (_graphics_device->presentation_parameters().PresentInterval())
            {
                case PresentInterval::Default:
                case PresentInterval::One:
                    glfwSwapInterval(1);
                    break;

                case PresentInterval::Two:
                    glfwSwapInterval(2);
                    break;

                case PresentInterval::Immediate:
                    glfwSwapInterval(0);
            }
        }

        bool GraphicsDeviceManager::begin_draw()
        {
            return true;
        }

        void GraphicsDeviceManager::end_draw()
        {
            _graphics_device->present();
        }

        void GraphicsDeviceManager::create_device()
        {
            // GLFW Initialization
            if (!glfwInit())
            {
                throw std::runtime_error("glfwInit failed");
            }

            _graphics_device = std::make_shared<GraphicsDevice>(GraphicsAdapter::DefaultAdapter()
                                                              , Graphics::GraphicsProfile::HiDef);
        }

        GraphicsDevice& GraphicsDeviceManager::graphics_device() const
        {
            return *_graphics_device;
        }
    }
}