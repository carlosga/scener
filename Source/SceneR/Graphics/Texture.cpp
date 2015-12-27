// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SceneR/Graphics/Texture.hpp"

#include "SceneR/Graphics/GraphicsDevice.hpp"

namespace SceneR
{
    namespace Graphics
    {
        bool Texture::is_compressed_surface_format(const SurfaceFormat& format) noexcept
        {
            return (format == SurfaceFormat::Dxt1
                 || format == SurfaceFormat::Dxt3
                 || format == SurfaceFormat::Dxt5);
        }

        Texture::Texture(gsl::not_null<GraphicsDevice*> graphicsDevice) noexcept
            : GraphicsResource { graphicsDevice }
        {
        }
    }
}
