// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Texture/SurfaceMipmap.hpp>

namespace SceneR
{
    namespace Texture
    {
        SurfaceMipmap::SurfaceMipmap()
        {
        }

        SurfaceMipmap::~SurfaceMipmap()
        {
        }

        SurfaceMipmap::index_type SurfaceMipmap::index() const
        {
            return _index;
        }

        SurfaceMipmap::size_type SurfaceMipmap::width() const
        {
            return _width;
        }

        SurfaceMipmap::size_type SurfaceMipmap::height() const
        {
            return _height;
        }

        const std::vector<std::uint8_t>& SurfaceMipmap::data() const
        {
            return _data;
        }
    }
}