// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_WINDOW_HPP
#define SCENER_GRAPHICS_WINDOW_HPP

#include <functional>
#include <memory>
#include <string>

#include <gsl/gsl>
#include <nod/nod.hpp>

#include "scener/graphics/vulkan/surface.hpp"

namespace scener::graphics
{
    class renderer;

    /// The window associated with a renderer.
    class window final
    {
    public:
        /// Initializes a new instance of the RendererWindow class.
        /// \param renderer the renderer instance owning the renderer window.
        window(gsl::not_null<renderer*> renderer) noexcept;

        /// Releases all resource being used by the current RendererWindow
        ~window();

    public:
        vulkan::display_surface* display_surface() const noexcept;

    public:
        /// Gets the renderer window title.
        const std::string& title() const noexcept;

        /// Sets the renderer window title.
        /// \param title the renderer window title.
        void title(const std::string& title) noexcept;

        /// Specifies whether to allow the user to resize the renderer window.
        /// \returns whether to allow the user to resize the renderer window.
        bool allow_user_resizing() const noexcept;

        /// Specifies whether to allow the user to resize the renderer window.
        /// \param allow_user_resizing true to allow window resizing; false otherwise.
        void allow_user_resizing(bool allow_user_resizing) noexcept;

        /// Gets a value indicating whether the underliying display surface has been closed.
        /// \return true if the underliying display surface has been closed; false otherwise.
        bool closed() const;

        /// Creates the underlying system window
        void create() noexcept;

    public:
        nod::connection connect_resize(std::function<void(std::uint32_t, std::uint32_t)>&& slot) noexcept;

    private:
        void show() const noexcept;
        void close() noexcept;
        void pool_events() const noexcept;

    private:
        window() = delete;
        window(const window& window) = delete;
        window& operator=(const window& window) = delete;

    private:
        renderer*                                _renderer          { nullptr };
        std::unique_ptr<vulkan::display_surface> _display_surface   { nullptr };
        std::string                              _title             { };
        nod::scoped_connection                   _close_connection  { };
        nod::scoped_connection                   _resize_connection { };
        bool                                     _closed            { false };

        friend class renderer;
    };
}

#endif // SCENER_GRAPHICS_WINDOW_HPP
