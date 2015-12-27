// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
//
// Based on https://github.com/gamedevtech/X11OpenGLWindow

#ifndef SCENER_CORE_GRAPHICS_DISPLAY_SURFACE_HPP
#define SCENER_CORE_GRAPHICS_DISPLAY_SURFACE_HPP

#include <X11/Xlib.h>

#include <gsl_assert.h>

#include <Graphics/OpenGL/DisplayDevice.hpp>

namespace SceneR
{
    namespace Graphics
    {
        class DisplaySurface final
        {
        public:
            DisplaySurface(DisplayDevice* display)
                : _display(display)
            {
            }

            ~DisplaySurface()
            {
                destroy();
            }

        public:
            const Drawable& handle() const noexcept
            {
                return _drawable;
            }

            bool create(std::uint32_t width, std::uint32_t height) noexcept
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
                }

                return (_drawable != 0);
            }

            void destroy() noexcept
            {
                if (_display && _drawable)
                {
                    XFreeColormap(_display->handle(), _drawable_attribs.colormap);
                    XDestroyWindow(_display->handle(), _drawable);
                    _display  = nullptr;
                    _drawable = 0;
                }
            }

            void clear() noexcept
            {
                Expects(_display  != nullptr);
                Expects(_drawable != 0);

                XClearWindow(_display->handle(), _drawable);
            }

            void show() noexcept
            {
                Expects(_display  != nullptr);
                Expects(_drawable != 0);

                XMapRaised(_display->handle(), _drawable);
                XRaiseWindow(_display->handle(), _drawable);
            }

            void pool_events() noexcept
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
                    else if (ev.type == ClientMessage)
                    {
                        if (static_cast<Atom>(ev.xclient.data.l[0]) == _atomWmDeleteDrawable)
                        {
                            _should_close = true;
                            break;
                        }
                        else
                        {
                            _events.push(ev);
                        }
                    }
                    else if (ev.type == DestroyNotify)
                    {
                        _should_close = true;
                        break;
                    }
                    else
                    {
                        _events.push(ev);
                    }
                }
            }

            bool should_close() const
            {
                return _should_close;
            }

            void swap_buffers() const
            {
                Expects(_display  != nullptr);
                Expects(_drawable != 0);

                // Present frame
                glXSwapBuffers(_display->handle(), _drawable);
            }

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
    }
}

#endif // SCENER_CORE_GRAPHICS_DISPLAY_SURFACE_HPP
