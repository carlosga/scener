// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
//
// Based on https://github.com/gamedevtech/X11OpenGLWindow

#ifndef SCENER_GRAPHICS_OPENGL_RENDERCONTEXT_HPP
#define SCENER_GRAPHICS_OPENGL_RENDERCONTEXT_HPP

#include <cstdint>
#include <string>

#include "SceneR/Graphics/OpenGL/Platform.hpp"

namespace SceneR { namespace Graphics { namespace OpenGL {

class DisplayDevice;
class DisplaySurface;

class RenderContext final
{
public:
    RenderContext(DisplayDevice* display, DisplaySurface* surface);
    ~RenderContext();

public:
    bool create() noexcept;

    bool is_direct_context() noexcept;

    void make_current() const noexcept;

    void destroy() noexcept;

    void enable_debug_output() const noexcept;

    void present_interval(std::int32_t interval) const noexcept;

    void present() const noexcept;

private:
    static bool isExtensionSupported(const std::string& extList, const std::string& extension) noexcept;

private:
    DisplayDevice*  _display { nullptr };
    DisplaySurface* _surface { nullptr };
    GLXContext      _context { 0 };
};

}}}

#endif // SCENER_GRAPHICS_OPENGL_RENDERCONTEXT_HPP
