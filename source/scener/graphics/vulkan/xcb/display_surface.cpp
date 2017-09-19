// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
// ==================================================================================================

#ifdef VK_USE_PLATFORM_XCB_KHR

#include "scener/graphics/vulkan/xcb/display_surface.hpp"

namespace scener::graphics::vulkan
{
    using scener::math::basic_rect;

    display_surface::display_surface(const std::string& title, const scener::math::basic_rect<std::uint32_t>& rect) noexcept
        : _window                { 0 }
        , _screen                { nullptr }
        , _connection            { nullptr }
        , _atom_wm_delete_window { nullptr }
        , _closing_signal        { }
        , _resize_signal         { }

    {
        create(title, rect);
    }

    display_surface::~display_surface() noexcept
    {
        destroy();
    }

    void display_surface::set_title(const std::string& title) noexcept
    {
        xcb_change_property(
            _connection
          , XCB_PROP_MODE_REPLACE
          , _window
          , XCB_ATOM_WM_NAME
          , XCB_ATOM_STRING
          , 8
          , title.size()
          , title.c_str());
    }

    xcb_connection_t* display_surface::connection() const noexcept
    {
        return _connection;
    }

    const xcb_window_t& display_surface::window() const noexcept
    {
        return _window;
    }

    basic_rect<std::uint32_t> display_surface::rect() const noexcept
    {
        xcb_get_geometry_cookie_t geomCookie = xcb_get_geometry(_connection, _window);  // window is a xcb_drawable_t
        xcb_get_geometry_reply_t* geom       = xcb_get_geometry_reply(_connection, geomCookie, nullptr);

        basic_rect<std::uint32_t> rect =
        {
            static_cast<std::uint32_t>(geom->x)
          , static_cast<std::uint32_t>(geom->y)
          , geom->width
          , geom->height
        };

        free (geom);

        return rect;
    }

    void display_surface::create(const std::string& title, const scener::math::basic_rect<std::uint32_t>& rect) noexcept
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
        xcb_create_window(c,                                        // Connection
                          XCB_COPY_FROM_PARENT,                     // depth (same as root)
                          w,                                        // window Id
                          s->root,                                  // parent window
                          0, 0,                                     // x, y
                          rect.size().width, rect.size().height,    // width, height
                          0,                                        // border_width
                          XCB_WINDOW_CLASS_INPUT_OUTPUT,            // class
                          s->root_visual,                           // visual
                          value_mask, value_list);                  // masks, not used yet */

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
        _window     = w;
        _screen     = s;
        _connection = c;

        /* Set window title */
        set_title(title);
    }

    void display_surface::clear() noexcept
    {
    }

    void display_surface::show() noexcept
    {
        xcb_flush(_connection);
    }

    void display_surface::pool_events() noexcept
    {
    }

    void display_surface::destroy() noexcept
    {
        if (_connection != nullptr)
        {
            if (_window != 0)
            {
                xcb_destroy_window(_connection, _window);
                _window = 0;
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

    nod::connection display_surface::connect_closing(std::function<void()>&& slot) noexcept
    {
        return _closing_signal.connect(slot);
    }

    nod::connection display_surface::connect_resize(std::function<void(std::int32_t, std::int32_t)>&& slot) noexcept
    {
        return _resize_signal.connect(slot);
    }
}

#endif
