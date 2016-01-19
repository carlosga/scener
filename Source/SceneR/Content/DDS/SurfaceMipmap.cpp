// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SceneR/Content/DDS/SurfaceMipmap.hpp"

namespace SceneR { namespace Content { namespace DDS {

SurfaceMipmap::SurfaceMipmap(index_type index, size_type width, size_type height, const gsl::span<std::uint8_t>& view) noexcept
    : _index  { index  }
    , _width  { width  }
    , _height { height }
    , _view   { view   }
{
}

SurfaceMipmap::index_type SurfaceMipmap::index() const noexcept
{
    return _index;
}

SurfaceMipmap::size_type SurfaceMipmap::width() const noexcept
{
    return _width;
}

SurfaceMipmap::size_type SurfaceMipmap::height() const noexcept
{
    return _height;
}

const gsl::span<std::uint8_t>& SurfaceMipmap::get_view() const noexcept
{
    return _view;
}

}}}
