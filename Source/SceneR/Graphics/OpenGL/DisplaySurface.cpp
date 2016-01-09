// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
// ==================================================================================================
// Based on https://github.com/gamedevtech/X11OpenGLWindow
// ==================================================================================================

#include "SceneR/Graphics/OpenGL/DisplaySurface.hpp"

#include <X11/Xatom.h>

#include <gsl_assert.h>

#include "SceneR/Graphics/OpenGL/DisplayDevice.hpp"

namespace SceneR { namespace Graphics { namespace OpenGL {

DisplaySurface::DisplaySurface(DisplayDevice* display)
    : _display(display)
{
}

DisplaySurface::~DisplaySurface()
{
    destroy();
}

const Drawable& DisplaySurface::handle() const noexcept
{
    return _drawable;
}

void DisplaySurface::title(const std::string& title) noexcept
{
    XChangeProperty(_display->handle()                                    /* connection to x server */
                  , _drawable                                             /* window whose property we want to change */
                  , _atomWmName                                           /* property name */
                  , XA_STRING                                             /* type of property */
                  , 8                                                     /* format of prop; can be 8, 16, 32 */
                  , PropModeReplace
                  , reinterpret_cast<const unsigned char*>(title.c_str()) /* actual data */
                  , title.size());                                        /* number of elements */
}

bool DisplaySurface::create(std::uint32_t width, std::uint32_t height) noexcept
{
    auto visual = _display->visual_info();
    auto root   = RootWindow(_display->handle(), _display->screen_id());

    // Open the window
    _drawable_attribs.border_pixel      = BlackPixel(_display->handle(), _display->screen_id());
    _drawable_attribs.background_pixel  = BlackPixel(_display->handle(), _display->screen_id());
    _drawable_attribs.override_redirect = true;
    _drawable_attribs.colormap          = XCreateColormap(_display->handle(), root, visual->visual, AllocNone);
    _drawable_attribs.event_mask        = ExposureMask;

    _drawable = XCreateWindow(_display->handle()
                            , root
                            , 0
                            , 0
                            , width
                            , height
                            , 0
                            , visual->depth
                            , InputOutput
                            , visual->visual, CWBackPixel | CWColormap | CWBorderPixel | CWEventMask
                            , &_drawable_attribs);

    if (_drawable)
    {
        // Redirect Close
        _atomWmDeleteDrawable = XInternAtom(_display->handle(), "WM_DELETE_WINDOW", False);
        XSetWMProtocols(_display->handle(), _drawable, &_atomWmDeleteDrawable, 1);

        // Window title
        _atomWmName = XInternAtom(_display->handle(), "WM_NAME", False);
    }

    return (_drawable != 0);
}

void DisplaySurface::destroy() noexcept
{
    if (_display && _drawable)
    {
        XFreeColormap(_display->handle(), _drawable_attribs.colormap);
        XDestroyWindow(_display->handle(), _drawable);
        _display  = nullptr;
        _drawable = 0;
    }
}

void DisplaySurface::clear() noexcept
{
    Expects(_display  != nullptr);
    Expects(_drawable != 0);

    XClearWindow(_display->handle(), _drawable);
}

void DisplaySurface::show() noexcept
{
    Expects(_display  != nullptr);
    Expects(_drawable != 0);

    XMapRaised(_display->handle(), _drawable);
    XRaiseWindow(_display->handle(), _drawable);
}

void DisplaySurface::pool_events() noexcept
{
    Expects(_display  != nullptr);
    Expects(_drawable != 0);

    XEvent ev;

    // Enter message loop
    while (XPending(_display->handle()) > 0)
    {
        XNextEvent(_display->handle(), &ev);
        if (ev.type == Expose)
        {
            XWindowAttributes attribs;
            XGetWindowAttributes(_display->handle(), _drawable, &attribs);
            //Resize(attribs.width, attribs.height);
        }
        else if (ev.type == KeymapNotify)
        {
            XRefreshKeyboardMapping(&ev.xmapping);
        }
        else if (ev.type == ClientMessage)
        {
            if (static_cast<Atom>(ev.xclient.data.l[0]) == _atomWmDeleteDrawable)
            {
                _should_close = true;
                break;
            }
        }
        else if (ev.type == DestroyNotify)
        {
            _should_close = true;
            break;
        }
    }
}

bool DisplaySurface::should_close() const
{
    return _should_close;
}

}}}
