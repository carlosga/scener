// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_CONTENT_DDS_SURFACE_HPP
#define SCENER_CONTENT_DDS_SURFACE_HPP

#include <cstddef>
#include <string>

#include <gsl.h>

#include "scener/content/dds/surface_mipmap.hpp"
#include "scener/graphics/surface_format.hpp"

namespace scener { namespace content { namespace dds {

/// Represents a DirectDraw surface.
class surface final
{
public:
    typedef std::size_t size_type;

public:
    /// Initializes a new instance of the Surface class.
    surface() = default;

    /// Destructor.
    ~surface() = default;

public:
    /// Loads the given file.
    void load(const std::string& filename) noexcept;

public:
    /// Gets the surface format.
    scener::graphics::surface_format format() const noexcept;

    /// Gets the surface width (in pixels).
    size_type width() const noexcept;

    /// Gets the surface height (in pixels).
    size_type height() const noexcept;

    /// Gets the surface mipmaps (when available).
    const std::vector<surface_mipmap>& mipmaps() const noexcept;

private:
    std::vector<std::uint8_t>       _buffer  { };
    std::vector<surface_mipmap>     _mipmaps { };
    gsl::span<std::uint8_t>         _view    { };
    scener::graphics::surface_format _format  { scener::graphics::surface_format::color };
    size_type                       _width   { 0 };
    size_type                       _height  { 0 };
};

}}}

#endif // SCENER_CONTENT_DDS_SURFACE_HPP
