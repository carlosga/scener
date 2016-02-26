// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SceneR/Graphics/GraphicsResource.hpp"

namespace scener { namespace graphics {

GraphicsResource::GraphicsResource(gsl::not_null<GraphicsDevice*> graphicsDevice) noexcept
    : name             { }
    , _graphics_device { graphicsDevice }
{
}

GraphicsDevice* GraphicsResource::graphics_device() const noexcept
{
    return _graphics_device;
}

}}
