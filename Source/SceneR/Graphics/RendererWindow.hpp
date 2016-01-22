// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_RENDERERWINDOW_HPP
#define SCENER_GRAPHICS_RENDERERWINDOW_HPP

#include <functional>
#include <memory>
#include <string>

#include <gsl.h>
#include <nod/nod.hpp>

namespace SceneR { namespace Graphics { namespace OpenGL {

class DisplayDevice;
class DisplaySurface;

}}}

namespace SceneR { namespace Graphics {

class Renderer;

/**
 * The window associated with a renderer.
 */
class RendererWindow final
{
public:
    /**
     * Initializes a new instance of the RendererWindow class.
     * @param renderer the renderer instance owning the renderer window.
     */
    RendererWindow(gsl::not_null<Renderer*> renderer) noexcept;

    /**
     * Releases all resource being used by the current RendererWindow
     */
    ~RendererWindow();

public:
    /**
     * Gets the renderer window title.
     */
    const std::string& title() const noexcept;

    /**
     * Sets the renderer window title.
     * @param title the renderer window title.
     */
    void title(const std::string& title) noexcept;

    /**
     * Specifies whether to allow the user to resize the renderer window.
     * @return whether to allow the user to resize the renderer window.
     */
    bool allow_user_resizing() const noexcept;

    /**
     * Specifies whether to allow the user to resize the renderer window.
     */
    void allow_user_resizing(bool allowUserResizing) noexcept;

    /**
     * @brief closed Gets a value indicating whether the underliying display surface has been closed.
     * @return a value indicating whether the underliying display surface has been closed.
     */
    bool closed() const;

public:
    nod::connection connect_resize(std::function<void(std::uint32_t, std::uint32_t)>&& slot) noexcept;

private:
    OpenGL::DisplayDevice* display_device() const noexcept;
    OpenGL::DisplaySurface* display_surface() const noexcept;
    void open() noexcept;
    void show() const noexcept;
    void close() noexcept;
    void initialize_connections() noexcept;
    void pool_events() const noexcept;

private:
    RendererWindow() = delete;
    RendererWindow(const RendererWindow& window) = delete;
    RendererWindow& operator=(const RendererWindow& window) = delete;

private:
    Renderer*                               _renderer          { nullptr };
    std::unique_ptr<OpenGL::DisplayDevice>  _displayDevice     { nullptr };
    std::unique_ptr<OpenGL::DisplaySurface> _displaySurface    { nullptr };
    std::string                             _title             { };
    nod::scoped_connection                  _close_connection  { };
    nod::scoped_connection                  _resize_connection { };
    bool                                    _closed            { false };

    friend class Renderer;
};

}}

#endif // SCENER_GRAPHICS_RENDERERWINDOW_HPP
