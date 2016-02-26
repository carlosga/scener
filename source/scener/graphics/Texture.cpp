// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/Texture.hpp"

#include "scener/graphics/GraphicsDevice.hpp"
#include "scener/graphics/SurfaceFormat.hpp"

namespace scener { namespace graphics {

Texture::Texture(gsl::not_null<GraphicsDevice*> graphicsDevice) noexcept
    : GraphicsResource { graphicsDevice }
{
}

}}
