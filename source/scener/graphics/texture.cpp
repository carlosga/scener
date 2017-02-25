// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/texture.hpp"

#include "scener/graphics/graphics_device.hpp"
#include "scener/graphics/surface_format.hpp"

namespace scener::graphics
{
    texture::texture(gsl::not_null<graphics_device*> device) noexcept
        : graphics_resource { device }
    {
    }
}
