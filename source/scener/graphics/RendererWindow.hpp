// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_RENDERERWINDOW_HPP
#define SCENER_GRAPHICS_RENDERERWINDOW_HPP

#include <functional>
#include <memory>
#include <string>

#include <gsl.h>
#include <nod/nod.hpp>

namespace scener { namespace graphics { namespace opengl {

class display_device;
class display_surface;

}}}

namespace scener { namespace graphics {

class renderer;

/// The window associated with a renderer.
class window final
{
public:
    /// Initializes a new instance of the RendererWindow class.
    /// \param renderer the renderer instance owning the renderer window.
    window(gsl::not_null<renderer*> renderer) noexcept;

    /// Releases all resource being used by the current RendererWindow
    ~window();

public:
    /// Gets the renderer window title.
    const std::string& title() const noexcept;

    /// Sets the renderer window title.
    /// \param title the renderer window title.
    void title(const std::string& title) noexcept;

    /// Specifies whether to allow the user to resize the renderer window.
    /// \returns whether to allow the user to resize the renderer window.
    bool allow_user_resizing() const noexcept;

    /// Specifies whether to allow the user to resize the renderer window.
    /// \param allowUserResizing true to allow window resizing; false otherwise.
    void allow_user_resizing(bool allowUserResizing) noexcept;

    /// Gets a value indicating whether the underliying display surface has been closed.
    /// \return true if the underliying display surface has been closed; false otherwise.
    bool closed() const;

public:
    nod::connection connect_resize(std::function<void(std::uint32_t, std::uint32_t)>&& slot) noexcept;

private:
    opengl::display_device* display_device() const noexcept;
    opengl::display_surface* display_surface() const noexcept;
    void open() noexcept;
    void show() const noexcept;
    void close() noexcept;
    void initialize_connections() noexcept;
    void pool_events() const noexcept;

private:
    window() = delete;
    window(const window& window) = delete;
    window& operator=(const window& window) = delete;

private:
    renderer*                               _renderer          { nullptr };
    std::unique_ptr<opengl::display_device>  _displayDevice     { nullptr };
    std::unique_ptr<opengl::display_surface> _displaySurface    { nullptr };
    std::string                             _title             { };
    nod::scoped_connection                  _close_connection  { };
    nod::scoped_connection                  _resize_connection { };
    bool                                    _closed            { false };

    friend class renderer;
};

}}

#endif // SCENER_GRAPHICS_RENDERERWINDOW_HPP
