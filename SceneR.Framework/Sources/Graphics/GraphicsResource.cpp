// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/GraphicsResource.hpp>

namespace SceneR
{
    namespace Graphics
    {
        GraphicsResource::GraphicsResource(Guide::not_null<GraphicsDevice*> graphicsDevice)
            : name             { }
            , _graphics_device { graphicsDevice }
        {
        }

        GraphicsDevice* GraphicsResource::graphics_device() const
        {
            return _graphics_device;
        }
    }
}
