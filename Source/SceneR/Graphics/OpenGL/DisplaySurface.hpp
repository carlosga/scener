// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
// ==================================================================================================
// Based on https://github.com/gamedevtech/X11OpenGLWindow
// ==================================================================================================

#ifndef SCENER_GRAPHICS_OPENGL_DISPLAYSURFACE_HPP
#define SCENER_GRAPHICS_OPENGL_DISPLAYSURFACE_HPP

#include <cstdint>
#include <queue>
#include <string>

#include <X11/Xlib.h>
#include <nod/nod.hpp>

namespace SceneR { namespace Graphics { namespace OpenGL {

class DisplayDevice;

/// Represents a X11 display surface (an X11 window).
class DisplaySurface final
{
public:
    /// Initializes a new instance of the DisplaySurface class with then given DisplayDevice.
    /// \param display the DisplayDevice instance used to create the surface.
    DisplaySurface(DisplayDevice* display);

    /// Releases all resources being used by this DisplaySurface instance.
    ~DisplaySurface();

public:
    /// Gets the X11 handle.
    const Drawable& handle() const noexcept;

    /// Sets the display surface title ( for window surfaces ).
    void title(const std::string& title) noexcept;

public:
    /// Creates the display surface with the given width and height.
    /// \param width the display surface width.
    /// \param height the display surface width.
    /// \returns true if the surface has been created; false otherwise.
    bool create(std::uint32_t width, std::uint32_t height) noexcept;

    /// Destroys this DisplaySurface instance.
    void destroy() noexcept;

    /// Clears the entire area of this display surface.
    void clear() noexcept;

    /// Shows the display surface.
    void show() noexcept;

    /// Process all the events that have been received from the X server.
    void pool_events() noexcept;

public:
    nod::connection connect_closing(std::function<void()>&& slot) noexcept;
    nod::connection connect_resize(std::function<void(std::uint32_t, std::uint32_t)>&& slot) noexcept;

private:
    DisplaySurface(const DisplaySurface&) = delete;
    DisplaySurface& operator=(const DisplaySurface&) = delete;

private:
    DisplayDevice*       _display              { nullptr };
    Drawable             _drawable             { 0 };
    XSetWindowAttributes _drawable_attribs     { };
    Atom                 _atomWmDeleteDrawable { };
    Atom                 _atomWmName           { };

    // signals
    nod::signal<void()> _closing_signal;
    nod::signal<void(std::uint32_t, std::uint32_t)> _resize_signal;
};

}}}

#endif // SCENER_GRAPHICS_OPENGL_DISPLAYSURFACE_HPP
