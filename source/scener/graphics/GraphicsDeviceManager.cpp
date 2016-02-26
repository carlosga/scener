// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/GraphicsDeviceManager.hpp"

#include "scener/graphics/GraphicsDevice.hpp"
#include "scener/graphics/Renderer.hpp"
#include "scener/graphics/RendererServiceContainer.hpp"
#include "scener/graphics/RendererWindow.hpp"

namespace scener { namespace graphics {

GraphicsDeviceManager::GraphicsDeviceManager(gsl::not_null<Renderer*> renderer) noexcept
    : _renderer { renderer }
{
    _renderer->services()->add_service<IGraphicsDeviceService>(*this);
}

void GraphicsDeviceManager::apply_changes() noexcept
{
    _graphics_device->presentation_parameters().back_buffer_width  = preferred_back_buffer_width;
    _graphics_device->presentation_parameters().back_buffer_height = preferred_back_buffer_height;
    _graphics_device->presentation_parameters().full_screen        = full_screen;

    _renderer->window()->title(window_title);
    _renderer->window()->allow_user_resizing(allow_user_resizing);

    _graphics_device->blend_state().apply();
    _graphics_device->rasterizer_state().apply();
    _graphics_device->depth_stencil_state().apply();
}

bool GraphicsDeviceManager::begin_draw() noexcept
{
    return true;
}

void GraphicsDeviceManager::end_draw() noexcept
{
    _graphics_device->present();
}

void GraphicsDeviceManager::create_device() noexcept
{
    _graphics_device = std::make_unique<GraphicsDevice>();
}

GraphicsDevice* GraphicsDeviceManager::graphics_device() const noexcept
{
    return _graphics_device.get();
}

}}
