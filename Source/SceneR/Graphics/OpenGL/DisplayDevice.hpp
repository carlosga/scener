// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
// ==================================================================================================
// Based on https://github.com/gamedevtech/X11OpenGLWindow
// ==================================================================================================

#ifndef SCENER_GRAPHICS_OPENGL_DISPLAYDEVICE_HPP
#define SCENER_GRAPHICS_OPENGL_DISPLAYDEVICE_HPP

#include <cstdint>

#include <SceneR/Graphics/OpenGL/Platform.hpp>

namespace SceneR { namespace Graphics { namespace OpenGL {

/// Represents a X11 Display.
class DisplayDevice final
{
public:
    /// Initializes a new instance of the DisplayDevice class.
    DisplayDevice() = default;

    /// Releases all resources being used by this DisplayDevice instance.
    ~DisplayDevice();

public:
    /// Gets a pointer to the X11 display handle.
    Display* handle() const noexcept;

    /// Gets the X11 screen id.
    int32_t screen_id() const noexcept;

    /// Gets the X11 display visual information.
    XVisualInfo* visual_info() const noexcept;

    /// Gets the selected frame buffer configuration for this DisplayDevice instance.
    const GLXFBConfig& frame_buffer_config() const noexcept;

    /// Opens a connection to the X server that controls a display.
    /// \returns true if the display has been opened; false otherwise.
    bool open() noexcept;

    /// Destroys the display.
    void destroy() noexcept;

    /// Flushes the output buffer and then waits until all requests have been received and processed by the X server.
    void sync() const noexcept;

private:
    bool check_glx_version() noexcept;
    void open_display() noexcept;
    bool configure_frame_buffer() noexcept;
    GLXFBConfig get_best_frame_buffer_configuration() const noexcept;

private:
    DisplayDevice(const DisplayDevice&) = delete;
    DisplayDevice& operator=(const DisplayDevice&) = delete;

private:
    // X11
    Display*     _display   { nullptr };
    Screen*      _screen    { nullptr };
    std::int32_t _screen_id { 0 };

    // GLX
    XVisualInfo* _visual_info { nullptr };
    GLXFBConfig  _fbc         { 0 };
};

}}}

#endif // SCENER_GRAPHICS_OPENGL_DISPLAYDEVICE_HPP
