// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_VIEWPORT_HPP
#define SCENER_GRAPHICS_VIEWPORT_HPP

#include <cstdint>

#include "scener/math/basic_rect.hpp"

namespace scener::graphics
{
    /// Represents the portion of the render target to receive draw calls.
    struct viewport final
    {
    public:
        /// Initializes a new instance of the ViewPort class
        viewport() noexcept;

        /// Initializes a new instance of the ViewPort class
        /// \param vx the x coordinate of the upper-left corner of the viewport in pixels.
        /// \param vy the y coordinate of the upper-left corner of the viewport in pixels.
        /// \param vwidth  the width of the viewport in pixels.
        /// \param vheight the height of the viewport in pixels.
        viewport(std::uint32_t vx, std::uint32_t vy, std::uint32_t vwidth, std::uint32_t vheight) noexcept;

    public:
        ///Gets the aspect ratio used by the viewport
        /// \returns the aspect ratio of the viewport.
        constexpr float aspect_ratio() const noexcept
        {
            return ((rect.width() > 0 && rect.height() > 0) ? rect.width() / rect.height() : 0.0f);
        }

    public:
        /// Gets or sets the viewport coordinates
        scener::math::basic_rect<std::uint32_t> rect;

        /// Gets or sets the minimum depth of the clip volume.
        float min_depth;

        /// Gets or sets the maximum depth of the clip volume.
        float max_depth;
    };
}

#endif // SCENER_GRAPHICS_VIEWPORT_HPP
