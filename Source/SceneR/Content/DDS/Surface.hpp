// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_CONTENT_DDS_SURFACE_HPP
#define SCENER_CONTENT_DDS_SURFACE_HPP

#include <cstddef>
#include <string>

#include <gsl.h>

#include "SceneR/Content/DDS/SurfaceMipmap.hpp"
#include "SceneR/Graphics/SurfaceFormat.hpp"

namespace SceneR { namespace Content { namespace DDS {

/// Represents a DirectDraw surface.
class Surface final
{
public:
    typedef std::size_t size_type;

public:
    /// Initializes a new instance of the Surface class.
    Surface() = default;

    /// Destructor.
    ~Surface() = default;

public:
    /// Loads the given file.
    void load(const std::string& filename) noexcept;

public:
    /// Gets the surface format.
    SceneR::Graphics::SurfaceFormat format() const noexcept;

    /// Gets the surface width (in pixels).
    size_type width() const noexcept;

    /// Gets the surface height (in pixels).
    size_type height() const noexcept;

    /// Gets the surface mipmaps (when available).
    const std::vector<SurfaceMipmap>& mipmaps() const noexcept;

private:
    std::vector<std::uint8_t>       _buffer  { };
    std::vector<SurfaceMipmap>      _mipmaps { };
    gsl::span<std::uint8_t>         _view    { };
    SceneR::Graphics::SurfaceFormat _format  { SceneR::Graphics::SurfaceFormat::color };
    size_type                       _width   { 0 };
    size_type                       _height  { 0 };
};

}}}

#endif // SCENER_CONTENT_DDS_SURFACE_HPP
