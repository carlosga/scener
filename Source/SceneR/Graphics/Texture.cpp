// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SceneR/Graphics/Texture.hpp"

#include "SceneR/Graphics/GraphicsDevice.hpp"
#include "SceneR/Graphics/SurfaceFormat.hpp"

namespace SceneR { namespace Graphics {

Texture::Texture(gsl::not_null<GraphicsDevice*> graphicsDevice) noexcept
    : GraphicsResource { graphicsDevice }
{
}

}}
