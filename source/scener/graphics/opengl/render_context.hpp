// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
//
// Based on https://github.com/gamedevtech/X11OpenGLWindow

#ifndef SCENER_GRAPHICS_OPENGL_RENDERCONTEXT_HPP
#define SCENER_GRAPHICS_OPENGL_RENDERCONTEXT_HPP

#include <string>

#include "scener/graphics/opengl/platform.hpp"

namespace scener { namespace graphics { namespace opengl {

class display_device;
class display_surface;

/// Represents an OpenGL context.
class render_context final
{
public:
    /// Initializes a new instance of the RenderContext class using the given display device and surface.
    /// \param display the display device used to create the render context.
    /// \param surface the display surface used to create the render context.
    render_context(display_device* display, display_surface* surface) noexcept;

    /// Releases all resources being used by this RenderContext instance.
    ~render_context();

public:
    /// Creates and initializes the OpenGL render context.
    bool create() noexcept;

    /// Gets a value indicating whether the current context has  direct rendering is enabled.
    bool is_direct_context() noexcept;

    /// Sets the current context as the active OpenGL rendering context.
    void make_current() const noexcept;

    /// Destroys this render context instance.
    void destroy() noexcept;

    /// Enables OpenGL debug output.
    void enable_debug_output() const noexcept;

    /// Specifies the minimum number of video frame periods per buffer swap.
    void present_interval(std::int32_t interval) const noexcept;

    /// Presents the display with the contents of the next buffer in the sequence of back buffers.
    void present() const noexcept;

private:
    static bool isExtensionSupported(const std::string& extensions, const std::string& extension) noexcept;

private:
    render_context(const render_context&) = delete;
    render_context& operator=(const render_context&) = delete;

private:
    display_device*  _display { nullptr };
    display_surface* _surface { nullptr };
    GLXContext       _context { 0 };
};

}}}

#endif // SCENER_GRAPHICS_OPENGL_RENDERCONTEXT_HPP
