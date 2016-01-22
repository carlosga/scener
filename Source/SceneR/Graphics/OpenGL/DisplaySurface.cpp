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
            _resize_signal(attribs.width, attribs.height);
        }
        else if (ev.type == KeymapNotify)
        {
            XRefreshKeyboardMapping(&ev.xmapping);
        }
        else if (ev.type == KeyPress)
        {
//            len = XLookupString(&ev.xkey, str, 25, &keysym, NULL);
//            if (len > 0) {
//                std::cout << "Key pressed: " << str << " - " << len << " - " << keysym <<'\n';
//            }
//            if (keysym == XK_Escape) {
//                running = false;
//            }
        }
        else if (ev.type == KeyRelease)
        {
//            len = XLookupString(&ev.xkey, str, 25, &keysym, NULL);
//            if (len > 0) {
//                std::cout << "Key released: " << str << " - " << len << " - " << keysym <<'\n';
//            }
        }
        else if (ev.type == MotionNotify)
        {
//            x = ev.xmotion.x;
//            y = ev.xmotion.y;
//            std::cout << "Mouse X:" << x << ", Y: " << y << "\n";
        }
        else if (ev.type == ButtonPress)
        {
//            if (ev.xbutton.button == 1) {
//                std::cout << "Left mouse down\n";
//            }
//            else if (ev.xbutton.button == 2) {
//                std::cout << "Middle mouse down\n";
//            }
//            else if (ev.xbutton.button == 3) {
//                std::cout << "Right mouse down\n";
//            }
//            else if (ev.xbutton.button == 4) {
//                std::cout << "Mouse scroll up\n";
//            }
//            else if (ev.xbutton.button == 5) {
//                std::cout << "Mouse scroll down\n";
//            }
        }
        else if (ev.type == ButtonRelease)
        {
//            if (ev.xbutton.button == 1) {
//                std::cout << "Left mouse up\n";
//            }
//            else if (ev.xbutton.button == 2) {
//                std::cout << "Middle mouse up\n";
//            }
//            else if (ev.xbutton.button == 3) {
//                std::cout << "Right mouse up\n";
//                running = false;
//            }
        }
        else if (ev.type == ClientMessage)
        {
            if (static_cast<Atom>(ev.xclient.data.l[0]) == _atomWmDeleteDrawable)
            {
                _closing_signal();
                break;
            }
        }
        else if (ev.type == DestroyNotify)
        {
            _closing_signal();
            break;
        }
    }
}

nod::connection DisplaySurface::connect_closing(std::function<void()>&& slot) noexcept
{
    return _closing_signal.connect(slot);
}

nod::connection DisplaySurface::connect_resize(std::function<void(std::uint32_t, std::uint32_t)>&& slot) noexcept
{
    return _resize_signal.connect(slot);
}

}}}
