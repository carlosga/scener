// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
// ==================================================================================================
// Based on https://github.com/gamedevtech/X11OpenGLWindow
// ==================================================================================================

#include "SceneR/Graphics/OpenGL/DisplayDevice.hpp"

#include <iostream>

namespace SceneR { namespace Graphics { namespace OpenGL {

DisplayDevice::~DisplayDevice()
{
    destroy();
}

Display* DisplayDevice::handle() const noexcept
{
    return _display;
}

uint32_t DisplayDevice::screen_id() const noexcept
{
    return _screen_id;
}

XVisualInfo* DisplayDevice::visual_info() const noexcept
{
    return _visual_info;
}

const GLXFBConfig& DisplayDevice::frame_buffer_config() const noexcept
{
    return _fbc;
}

bool DisplayDevice::open() noexcept
{
    XInitThreads();

    open_display();

    if (!_display)
    {
        return false;
    }

    if (!gladLoadGLX(_display, _screen_id))
    {
        std::cerr << "GLX 1.4 or greater is required." << std::endl;
        destroy();
        return false;
    }

    if (!check_glx_version())
    {
        std::cerr << "GLX 1.4 or greater is required." << std::endl;
        destroy();
        return false;
    }

    if (!configure_frame_buffer())
    {
        destroy();
        return false;
    }

    return true;
}

void DisplayDevice::destroy() noexcept
{
    if (_visual_info != 0)
    {
        XFree(_visual_info);
        _visual_info = nullptr;
    }

    if (_display)
    {
        XCloseDisplay(_display);

        _display = nullptr;
    }
}

void DisplayDevice::sync() const noexcept
{
    XSync(_display, false);
}

bool DisplayDevice::check_glx_version() noexcept
{
    // Check GLX version
    GLint majorGLX = 0;
    GLint minorGLX = 0;
    glXQueryVersion(_display, &majorGLX, &minorGLX);

    return (majorGLX == 1 && minorGLX == 4);
}

void DisplayDevice::open_display() noexcept
{
    // Open the display
    _display = XOpenDisplay(NULL);
    if (_display == nullptr)
    {
        std::cout << "Could not open display\n";
        return;
    }

    _screen    = DefaultScreenOfDisplay(_display);
    _screen_id = DefaultScreen(_display);
}

bool DisplayDevice::configure_frame_buffer() noexcept
{
    // Pick the FB config/visual with the most samples per pixel
    _fbc = get_best_frame_buffer_configuration();

    if (_fbc == 0)
    {
        std::cout << "Failed to retrieve framebuffer.\n";
        return false;
    }

    _visual_info = glXGetVisualFromFBConfig(_display, _fbc);
    if (_visual_info == 0)
    {
        std::cerr << "Could not create correct visual window." << std::endl;
        return false;
    }

    if (_screen_id != _visual_info->screen)
    {
        std::cout << "screenId(" << std::to_string(_screen_id) << ") does not match visual->screen(" << _visual_info->screen << ")." << std::endl;
        return false;
    }

    _fbc = get_best_frame_buffer_configuration();

    return true;
}

GLXFBConfig DisplayDevice::get_best_frame_buffer_configuration() const noexcept
{
    std::int32_t glxAttribs[] =
    {
        GLX_X_RENDERABLE  , true,
        GLX_DRAWABLE_TYPE , GLX_WINDOW_BIT,
        GLX_RENDER_TYPE   , GLX_RGBA_BIT,
        GLX_X_VISUAL_TYPE , GLX_TRUE_COLOR,
        GLX_RED_SIZE      , 8,
        GLX_GREEN_SIZE    , 8,
        GLX_BLUE_SIZE     , 8,
        GLX_ALPHA_SIZE    , 8,
        GLX_DEPTH_SIZE    , 24,
        GLX_STENCIL_SIZE  , 8,
        GLX_DOUBLEBUFFER  , true,
        0
    };

    std::int32_t fbcount;
    GLXFBConfig* fbc = glXChooseFBConfig(_display, _screen_id, glxAttribs, &fbcount);
    if (!fbc)
    {
        return 0;
    }

    std::int32_t best_fbc       = -1;
    std::int32_t worst_fbc      = -1;
    std::int32_t best_num_samp  = -1;
    std::int32_t worst_num_samp = 999;

    for (int32_t i = 0; i < fbcount; ++i)
    {
        XVisualInfo* vi = glXGetVisualFromFBConfig(_display, fbc[i]);
        if (vi != 0)
        {
            std::int32_t samp_buf;
            std::int32_t samples;
            glXGetFBConfigAttrib(_display, fbc[i], GLX_SAMPLE_BUFFERS, &samp_buf);
            glXGetFBConfigAttrib(_display, fbc[i], GLX_SAMPLES       , &samples);

            if (best_fbc < 0 || (samp_buf && samples > best_num_samp))
            {
                best_fbc      = i;
                best_num_samp = samples;
            }
            if (worst_fbc < 0 || !samp_buf || samples < worst_num_samp)
            {
                worst_fbc = i;
            }
            worst_num_samp = samples;
        }
        XFree(vi);
    }

    GLXFBConfig result = fbc[best_fbc];
    XFree(fbc); // Make sure to free this!

    return result;
}

}}}