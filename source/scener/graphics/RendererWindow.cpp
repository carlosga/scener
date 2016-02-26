// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/RendererWindow.hpp"

#include "scener/graphics/GraphicsDevice.hpp"
#include "scener/graphics/GraphicsDeviceManager.hpp"
#include "scener/graphics/Renderer.hpp"
#include "scener/graphics/opengl/DisplayDevice.hpp"
#include "scener/graphics/opengl/DisplaySurface.hpp"

namespace scener { namespace graphics {

using scener::graphics::opengl::DisplayDevice;
using scener::graphics::opengl::DisplaySurface;

window::window(gsl::not_null<renderer*> renderer) noexcept
    : _renderer { renderer }
{
}

window::~window()
{
    close();
}

const std::string& window::title() const noexcept
{
    return _title;
}

void window::title(const std::string& title) noexcept
{
    _title = title;
    _displaySurface->title(title);
}

bool window::allow_user_resizing() const noexcept
{
    return _renderer->_device_manager->allow_user_resizing;
}

void window::allow_user_resizing(bool allowUserResizing) noexcept
{
    _renderer->_device_manager->allow_user_resizing = allowUserResizing;
}

bool window::closed() const
{
    return _closed;
}

nod::connection window::connect_resize(std::function<void(uint32_t, uint32_t)>&& slot) noexcept
{
    return _displaySurface->connect_resize(std::move(slot));
}

DisplayDevice* window::display_device() const noexcept
{
    return _displayDevice.get();
}

DisplaySurface* window::display_surface() const noexcept
{
    return _displaySurface.get();
}

void window::open() noexcept
{
    auto width  = _renderer->_device_manager->preferred_back_buffer_width;
    auto height = _renderer->_device_manager->preferred_back_buffer_height;

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

void window::show() const noexcept
{
    _displaySurface->clear();
    _displaySurface->show();
}

void window::close() noexcept
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

void window::initialize_connections() noexcept
{
    _close_connection = _displaySurface->connect_closing([&]() {
        _closed = true;
        _close_connection.disconnect();
        _resize_connection.disconnect();
    });
    _resize_connection = _displaySurface->connect_resize([&](std::uint32_t width, std::uint32_t height) {
        _renderer->device()->viewport().width  = width;
        _renderer->device()->viewport().height = height;
        _renderer->device()->viewport().update();
    });
}

void window::pool_events() const noexcept
{
    _displaySurface->pool_events();
}

}}
