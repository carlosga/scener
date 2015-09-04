// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/GraphicsResource.hpp>

namespace SceneR
{
    namespace Graphics
    {
        GraphicsResource::GraphicsResource(GraphicsDevice& graphicsDevice)
            : name             { }
            , tag              { }
            , _graphics_device { graphicsDevice }
        {
        }

        GraphicsResource::~GraphicsResource()
        {
        }

        GraphicsDevice& GraphicsResource::graphics_device() const
        {
            return _graphics_device;
        }
    }
}
