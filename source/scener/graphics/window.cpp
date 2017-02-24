// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/window.hpp"

#include "scener/graphics/graphics_device.hpp"
#include "scener/graphics/graphics_device_manager.hpp"
#include "scener/graphics/renderer.hpp"

namespace scener { namespace graphics {

window::window(gsl::not_null<renderer*> renderer) noexcept
    : _renderer { renderer }
{
}

window::~window()
{
    close();
}

opengl::display_surface* window::display_surface() const noexcept
{
    return _display_surface.get();
}

const std::string& window::title() const noexcept
{
    return _title;
}

void window::title(const std::string& title) noexcept
{
    _title = title;
    _display_surface->title(title);
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
    return _display_surface->connect_resize(std::move(slot));
}

void window::open() noexcept
{
    auto width  = _renderer->_device_manager->preferred_back_buffer_width;
    auto height = _renderer->_device_manager->preferred_back_buffer_height;

    _display_surface = std::make_unique<opengl::display_surface>(_renderer->device()->display_device());

    if (!_display_surface->create(width, height))
    {
        throw std::runtime_error("An error has occurred while creating the display surface.");
    }

    initialize_connections();
}

void window::show() const noexcept
{
    _display_surface->clear();
    _display_surface->show();
}

void window::close() noexcept
{
    if (_display_surface.get())
    {
        _display_surface->destroy();
        _display_surface = nullptr;
    }
}

void window::initialize_connections() noexcept
{
    _close_connection = _display_surface->connect_closing([&]() {
        _closed = true;
        _close_connection.disconnect();
        _resize_connection.disconnect();
    });
    _resize_connection = _display_surface->connect_resize([&](std::uint32_t width, std::uint32_t height) {
        _renderer->device()->viewport().width  = width;
        _renderer->device()->viewport().height = height;
        _renderer->device()->viewport().update();
    });
}

void window::pool_events() const noexcept
{
    _display_surface->pool_events();
}

}}
