// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_CONTENT_DDS_SURFACEMIPMAP_HPP
#define SCENER_CONTENT_DDS_SURFACEMIPMAP_HPP

#include <cstddef>
#include <cstdint>
#include <vector>

#include <gsl.h>

namespace SceneR { namespace Content { namespace DDS {

class SurfaceMipmap final
{
public:
    typedef std::size_t index_type;
    typedef std::size_t size_type;

public:
    SurfaceMipmap(index_type index, size_type width, size_type height, const gsl::span<std::uint8_t>& view) noexcept;
    ~SurfaceMipmap() = default;

public:
    index_type index() const noexcept;
    size_type  width() const noexcept;
    size_type  height() const noexcept;
    const gsl::span<std::uint8_t>& get_view() const noexcept;

private:
    index_type              _index;
    size_type               _width;
    size_type               _height;
    gsl::span<std::uint8_t> _view;
};

}}}

#endif // SCENER_CONTENT_DDS_SURFACEMIPMAP_HPP
