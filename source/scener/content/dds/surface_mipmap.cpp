// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/content/dds/surface_mipmap.hpp"

namespace scener::content::dds
{
    surface_mipmap::surface_mipmap(index_type index, size_type width, size_type height, const gsl::span<std::uint8_t>& view) noexcept
        : _index  { index  }
        , _width  { width  }
        , _height { height }
        , _view   { view   }
    {
    }

    surface_mipmap::index_type surface_mipmap::index() const noexcept
    {
        return _index;
    }

    surface_mipmap::size_type surface_mipmap::width() const noexcept
    {
        return _width;
    }

    surface_mipmap::size_type surface_mipmap::height() const noexcept
    {
        return _height;
    }

    const gsl::span<std::uint8_t>& surface_mipmap::get_view() const noexcept
    {
        return _view;
    }
}
