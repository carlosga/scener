// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
// ==================================================================================================
// Based on https://github.com/gamedevtech/X11OpenGLWindow
// ==================================================================================================

#ifndef SCENER_GRAPHICS_OPENGL_DISPLAYSURFACE_HPP
#define SCENER_GRAPHICS_OPENGL_DISPLAYSURFACE_HPP

#include <cstdint>
#include <queue>

#include <X11/Xlib.h>

namespace SceneR { namespace Graphics { namespace OpenGL {

class DisplayDevice;

class DisplaySurface final
{
public:
    DisplaySurface(DisplayDevice* display);
    ~DisplaySurface();

public:
    const Drawable& handle() const noexcept;

    bool create(std::uint32_t width, std::uint32_t height) noexcept;

    void destroy() noexcept;

    void clear() noexcept;

    void show() noexcept;

    void pool_events() noexcept;

    bool should_close() const;

    void swap_buffers() const;

private:
    DisplayDevice*       _display;
    Drawable             _drawable;
    XSetWindowAttributes _drawable_attribs;
    Atom                 _atomWmDeleteDrawable;

    // Misc
    bool _should_close = false;

    // Events
    std::queue<XEvent> _events;
};

}}}

#endif // SCENER_GRAPHICS_OPENGL_DISPLAYSURFACE_HPP