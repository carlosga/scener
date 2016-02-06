// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_VIEWPORT_HPP
#define SCENER_GRAPHICS_VIEWPORT_HPP

#include <cstdint>

namespace SceneR { namespace Graphics {

/// Represents the portion of the render target to receive draw calls.
struct Viewport final
{
public:
    /// Initializes a new instance of the ViewPort class
    Viewport() noexcept;

    /// Initializes a new instance of the ViewPort class
    /// \param x the x coordinate of the upper-left corner of the viewport in pixels.
    /// \param y the y coordinate of the upper-left corner of the viewport in pixels.
    /// \param width  the width of the viewport in pixels.
    /// \param height the height of the viewport in pixels.
    Viewport(std::uint32_t x, std::uint32_t y, std::uint32_t width, std::uint32_t height) noexcept;

public:
    ///Gets the aspect ratio used by the viewport
    /// \returns the aspect ratio of the viewport.
    constexpr float aspect_ratio() const noexcept
    {
        return ((width > 0 && height > 0) ? static_cast<float>(width) / static_cast<float>(height) : 0.0f);
    }

    /// Updates the viewport.
    void update() const noexcept;

public:
    /// Gets or sets the pixel coordinate of the upper-left corner of the viewport on the render-target surface.
    std::uint32_t x;

    /// Gets or sets the pixel coordinate of the upper-left corner of the viewport on the render-target surface.
    std::uint32_t y;

    /// Gets or sets the width dimension of the viewport on the render-target surface, in pixels.
    std::uint32_t width;

    /// Gets or sets the height dimension of the viewport on the render-target surface, in pixels.
    std::uint32_t height;

    /// Gets or sets the minimum depth of the clip volume.
    float min_depth;

    /// Gets or sets the maximum depth of the clip volume.
    float max_depth;
};

}}

#endif // SCENER_GRAPHICS_VIEWPORT_HPP
