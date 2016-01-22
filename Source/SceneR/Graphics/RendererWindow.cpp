// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SceneR/Graphics/RendererWindow.hpp"

#include "SceneR/Graphics/GraphicsDevice.hpp"
#include "SceneR/Graphics/GraphicsDeviceManager.hpp"
#include "SceneR/Graphics/Renderer.hpp"
#include "SceneR/Graphics/OpenGL/DisplayDevice.hpp"
#include "SceneR/Graphics/OpenGL/DisplaySurface.hpp"

namespace SceneR { namespace Graphics {

using SceneR::Graphics::OpenGL::DisplayDevice;
using SceneR::Graphics::OpenGL::DisplaySurface;

RendererWindow::RendererWindow(gsl::not_null<Renderer*> renderer) noexcept
    : _renderer { renderer }
{
}

RendererWindow::~RendererWindow()
{
    close();
}

const std::string& RendererWindow::title() const noexcept
{
    return _title;
}

void RendererWindow::title(const std::string& title) noexcept
{
    _title = title;
    _displaySurface->title(title);
}

bool RendererWindow::allow_user_resizing() const noexcept
{
    return _renderer->_graphics_device_manager->allow_user_resizing;
}

void RendererWindow::allow_user_resizing(bool allowUserResizing) noexcept
{
    _renderer->_graphics_device_manager->allow_user_resizing = allowUserResizing;
}

bool RendererWindow::closed() const
{
    return _closed;
}

nod::connection RendererWindow::connect_resize(std::function<void(uint32_t, uint32_t)>&& slot) noexcept
{
    return _displaySurface->connect_resize(std::move(slot));
}

DisplayDevice* RendererWindow::display_device() const noexcept
{
    return _displayDevice.get();
}

DisplaySurface* RendererWindow::display_surface() const noexcept
{
    return _displaySurface.get();
}

void RendererWindow::open() noexcept
{
    auto width  = _renderer->_graphics_device_manager->preferred_back_buffer_width;
    auto height = _renderer->_graphics_device_manager->preferred_back_buffer_height;

    _displayDevice  = std::make_unique<DisplayDevice>();
    _displaySurface = std::make_unique<DisplaySurface>(_displayDevice.get());

    if (!_displayDevice->open())
    {
        throw std::runtime_error("An error has occurred while opening the display device.");
    }

    if (!_displaySurface->create(width, height))
    {
        throw std::runtime_error("An error has occurred while creatring the display surface.");
    }

    initialize_connections();
}

void RendererWindow::show() const noexcept
{
    _displaySurface->clear();
    _displaySurface->show();
}

void RendererWindow::close() noexcept
{
    if (_displaySurface.get())
    {
        _displaySurface->destroy();
        _displaySurface = nullptr;
    }
    if (_displayDevice.get())
    {
        _displayDevice->destroy();
        _displayDevice = nullptr;
    }
}

void RendererWindow::initialize_connections() noexcept
{
    _close_connection = _displaySurface->connect_closing([&]() {
        _closed = true;
        _close_connection.disconnect();
        _resize_connection.disconnect();
    });
    _resize_connection = _displaySurface->connect_resize([&](std::uint32_t width, std::uint32_t height) {
        _renderer->graphics_device()->viewport().width  = width;
        _renderer->graphics_device()->viewport().height = height;
        _renderer->graphics_device()->viewport().update();
    });
}

void RendererWindow::pool_events() const noexcept
{
    _displaySurface->pool_events();
}

}}
