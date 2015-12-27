// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SceneR/Graphics/GraphicsDeviceManager.hpp"

#include "SceneR/Graphics/GraphicsDevice.hpp"
#include "SceneR/Graphics/PresentInterval.hpp"
#include "SceneR/Graphics/Renderer.hpp"
#include "SceneR/Graphics/RendererServiceContainer.hpp"
#include "SceneR/Graphics/RendererWindow.hpp"

namespace SceneR
{
    namespace Graphics
    {
        GraphicsDeviceManager::GraphicsDeviceManager(gsl::not_null<Renderer*> renderer)
            : _renderer { renderer }
        {
            _renderer->services()->add_service<IGraphicsDeviceService>(*this);
        }

        void GraphicsDeviceManager::dispose()
        {
            if (_graphics_device.get())
            {
                _graphics_device->dispose();
                _graphics_device = nullptr;
            }
        }

        void GraphicsDeviceManager::apply_changes()
        {
            _graphics_device->presentation_parameters().back_buffer_width  = preferred_back_buffer_width;
            _graphics_device->presentation_parameters().back_buffer_height = preferred_back_buffer_height;
            _graphics_device->presentation_parameters().full_screen        = full_screen;

            _renderer->window()->title(window_title);
            _renderer->window()->allow_user_resizing(allow_user_resizing);

            _graphics_device->viewport().width  = preferred_back_buffer_width;
            _graphics_device->viewport().height = preferred_back_buffer_height;
            _graphics_device->viewport().update();

            _graphics_device->blend_state().apply();
            _graphics_device->rasterizer_state().apply();
            _graphics_device->depth_stencil_state().apply();
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
            _graphics_device = std::make_unique<GraphicsDevice>();
        }

        GraphicsDevice* GraphicsDeviceManager::graphics_device() const noexcept
        {
            return _graphics_device.get();
        }
    }
}
