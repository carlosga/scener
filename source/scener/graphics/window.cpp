// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/window.hpp"

#include "scener/graphics/graphics_device.hpp"
#include "scener/graphics/graphics_device_manager.hpp"
#include "scener/graphics/renderer.hpp"
#include "scener/graphics/opengl/display_device.hpp"
#include "scener/graphics/opengl/display_surface.hpp"

namespace scener { namespace graphics {

window::window(gsl::not_null<graphics::renderer*> renderer) noexcept
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

void window::allow_user_resizing(bool allow_user_resizing) noexcept
{
    _renderer->_device_manager->allow_user_resizing = allow_user_resizing;
}

bool window::closed() const
{
    return _closed;
}

nod::connection window::connect_resize(std::function<void(uint32_t, uint32_t)>&& slot) noexcept
{
    return _displaySurface->connect_resize(std::move(slot));
}

opengl::display_device* window::display_device() const noexcept
{
    return _displayDevice.get();
}

opengl::display_surface* window::display_surface() const noexcept
{
    return _displaySurface.get();
}

void window::open() noexcept
{
    auto width  = _renderer->_device_manager->preferred_back_buffer_width;
    auto height = _renderer->_device_manager->preferred_back_buffer_height;

    _displayDevice  = std::make_unique<opengl::display_device>();
    _displaySurface = std::make_unique<opengl::display_surface>(_displayDevice.get());

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
