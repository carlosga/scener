// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_CONTENT_DDS_SURFACE_HPP
#define SCENER_CONTENT_DDS_SURFACE_HPP

#include <cstddef>
#include <string>

#include "SceneR/Content/DDS/SurfaceMipmap.hpp"
#include "SceneR/Graphics/SurfaceFormat.hpp"

namespace SceneR { namespace Content { namespace DDS {

class Surface final
{
public:
    typedef std::size_t size_type;

public:
    Surface() = default;
    ~Surface() = default;

public:
    void load(const std::string& filename);

public:
    const SceneR::Graphics::SurfaceFormat& format() const noexcept;
    size_type width() const noexcept;
    size_type height() const noexcept;
    const std::vector<SurfaceMipmap>& mipmaps() const noexcept;

private:
    std::vector<std::uint8_t> read_file(const std::string& filename) const noexcept;

private:
    SceneR::Graphics::SurfaceFormat _format;
    size_type                       _width;
    size_type                       _height;
    std::vector<SurfaceMipmap>      _mipmaps;
};

}}}

#endif // SCENER_CONTENT_DDS_SURFACE_HPP
