// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
// ==================================================================================================
// Based on https://github.com/gamedevtech/X11OpenGLWindow
// ==================================================================================================

#ifdef VK_USE_PLATFORM_XCB_KHR

#include "scener/graphics/vulkan/display_surface.hpp"
#include "scener/graphics/vulkan/vulkan_result.hpp"

namespace scener::graphics::vulkan
{
    display_surface::display_surface(gsl::not_null<vk::Instance*> vk_instance) noexcept
        : _xcb_window            { 0 }
        , _screen                { nullptr }
        , _connection            { nullptr }
        , _atom_wm_delete_window { nullptr }
        , _vk_instance           { vk_instance }
        , _vk_surface            { }
    {
    }

    display_surface::~display_surface() noexcept
    {
        destroy();
    }

    void display_surface::title(const std::string& title) noexcept
    {
    }

    void display_surface::create(std::uint32_t width, std::uint32_t height) noexcept
    {
        xcb_connection_t*     c;
        const xcb_setup_t*    setup;
        xcb_screen_iterator_t iterator;
        xcb_screen_t*         s;
        xcb_window_t          w;
        std::int32_t          count;

        std::uint32_t value_mask;
        std::uint32_t value_list[32];

        /* Open the connection to the X server. */
        c = xcb_connect(NULL, &count);

        setup = xcb_get_setup(c);

        /* Get the first screen */
        iterator = xcb_setup_roots_iterator(setup);

        while (count-- > 0)
        {
            xcb_screen_next(&iterator);
        }

        s = iterator.data;

        /* Ask for our window's Id */
        w = xcb_generate_id(c);

        /* setup surface masks */
        value_mask    = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
        value_list[0] = s->black_pixel;
        value_list[1] =
            XCB_EVENT_MASK_KEY_RELEASE 
          | XCB_EVENT_MASK_KEY_PRESS 
          | XCB_EVENT_MASK_EXPOSURE 
          | XCB_EVENT_MASK_STRUCTURE_NOTIFY 
          | XCB_EVENT_MASK_POINTER_MOTION 
          | XCB_EVENT_MASK_BUTTON_PRESS 
          | XCB_EVENT_MASK_BUTTON_RELEASE;

        /* Create the window */
        xcb_create_window(c,                               // Connection
                          XCB_COPY_FROM_PARENT,            // depth (same as root)
                          w,                               // window Id
                          s->root,                         // parent window
                          0, 0,                            // x, y
                          width, height,                   // width, height
                          0,                               // border_width
                          XCB_WINDOW_CLASS_INPUT_OUTPUT,   // class
                          s->root_visual,                  // visual
                          value_mask, value_list);         // masks, not used yet */

        /* Redirect Close */
        xcb_intern_atom_cookie_t cookie  = xcb_intern_atom(c, 1, 12, "WM_PROTOCOLS");
        xcb_intern_atom_reply_t* reply   = xcb_intern_atom_reply(c, cookie, NULL);
        xcb_intern_atom_cookie_t cookie2 = xcb_intern_atom(c, 0, 16, "WM_DELETE_WINDOW");

        _atom_wm_delete_window = xcb_intern_atom_reply(c, cookie2, NULL);

        xcb_change_property(c, XCB_PROP_MODE_REPLACE, w, (*reply).atom, 4, 32, 1, &(*_atom_wm_delete_window).atom);

        free(reply);

        /* Map the window on the screen */
        xcb_map_window(c, w);

        /* update instance members */
        _xcb_window = w;
        _screen     = s;
        _connection = c;

        auto create_info = vk::XcbSurfaceCreateInfoKHR().setConnection(_connection).setWindow(_xcb_window);
        auto result      = _vk_instance->createXcbSurfaceKHR(&create_info, nullptr, &_vk_surface);

        check_result(result);
    }

    void display_surface::destroy() noexcept
    {
        if (_connection != nullptr)
        {
            if (_xcb_window != 0)
            {
                xcb_destroy_window(_connection, _xcb_window);
                _xcb_window = 0;
            }
            xcb_disconnect(_connection);
            _connection = nullptr;
        }
        if (_atom_wm_delete_window)
        {
            free(_atom_wm_delete_window);
            _atom_wm_delete_window = nullptr;
        }
    }

    void display_surface::clear() noexcept
    {
    }

    void display_surface::show() noexcept
    {
        xcb_flush(_connection);
    }

    vk::Extent2D display_surface::get_extent(const vk::SurfaceCapabilitiesKHR& capabilities) const noexcept
    {
        VkExtent2D extent;

        // The extent is typically the size of the window we created the surface from.
        // However if Vulkan returns -1 then simply substitute the window size.
        if (capabilities.currentExtent.width == UINT32_MAX)
        {
            xcb_get_geometry_cookie_t geomCookie = xcb_get_geometry(_connection, _xcb_window);  // window is a xcb_drawable_t
            xcb_get_geometry_reply_t* geom       = xcb_get_geometry_reply(_connection, geomCookie, nullptr);

            extent.width  = geom->width;
            extent.height = geom->height;

            free (geom);
        }
        else
        {
            extent = capabilities.currentExtent;
        }

        return extent;
    }

    void display_surface::pool_events() noexcept
    {
    //     Expects(_display  != nullptr);
    //     Expects(_drawable != 0);

    //     XEvent ev;

    //     // Enter message loop
    //     while (XPending(_display->handle()) > 0)
    //     {
    //         XNextEvent(_display->handle(), &ev);
    //         if (ev.type == Expose)
    //         {
    //             XWindowAttributes attribs;
    //             XGetWindowAttributes(_display->handle(), _drawable, &attribs);
    //             _resize_signal(attribs.width, attribs.height);
    //         }
    //         else if (ev.type == KeymapNotify)
    //         {
    //             XRefreshKeyboardMapping(&ev.xmapping);
    //         }
    //         else if (ev.type == KeyPress)
    //         {
    // //            len = XLookupString(&ev.xkey, str, 25, &keysym, NULL);
    // //            if (len > 0) {
    // //                std::cout << "Key pressed: " << str << " - " << len << " - " << keysym <<'\n';
    // //            }
    // //            if (keysym == XK_Escape) {
    // //                running = false;
    // //            }
    //         }
    //         else if (ev.type == KeyRelease)
    //         {
    // //            len = XLookupString(&ev.xkey, str, 25, &keysym, NULL);
    // //            if (len > 0) {
    // //                std::cout << "Key released: " << str << " - " << len << " - " << keysym <<'\n';
    // //            }
    //         }
    //         else if (ev.type == MotionNotify)
    //         {
    // //            x = ev.xmotion.x;
    // //            y = ev.xmotion.y;
    // //            std::cout << "Mouse X:" << x << ", Y: " << y << "\n";
    //         }
    //         else if (ev.type == ButtonPress)
    //         {
    // //            if (ev.xbutton.button == 1) {
    // //                std::cout << "Left mouse down\n";
    // //            }
    // //            else if (ev.xbutton.button == 2) {
    // //                std::cout << "Middle mouse down\n";
    // //            }
    // //            else if (ev.xbutton.button == 3) {
    // //                std::cout << "Right mouse down\n";
    // //            }
    // //            else if (ev.xbutton.button == 4) {
    // //                std::cout << "Mouse scroll up\n";
    // //            }
    // //            else if (ev.xbutton.button == 5) {
    // //                std::cout << "Mouse scroll down\n";
    // //            }
    //         }
    //         else if (ev.type == ButtonRelease)
    //         {
    // //            if (ev.xbutton.button == 1) {
    // //                std::cout << "Left mouse up\n";
    // //            }
    // //            else if (ev.xbutton.button == 2) {
    // //                std::cout << "Middle mouse up\n";
    // //            }
    // //            else if (ev.xbutton.button == 3) {
    // //                std::cout << "Right mouse up\n";
    // //                running = false;
    // //            }
    //         }
    //         else if (ev.type == ClientMessage)
    //         {
    //             if (static_cast<Atom>(ev.xclient.data.l[0]) == _atomWmDeleteDrawable)
    //             {
    //                 _closing_signal();
    //                 break;
    //             }
    //         }
    //         else if (ev.type == DestroyNotify)
    //         {
    //             _closing_signal();
    //             break;
    //         }
    //    }
    }
}

#endif
