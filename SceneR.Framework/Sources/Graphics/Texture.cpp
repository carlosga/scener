// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/Texture.hpp>

#include <Graphics/GraphicsDevice.hpp>

using namespace SceneR::Graphics;

System::Boolean Texture::IsCompressedSurfaceFormat(const SurfaceFormat& format)
{
    return (format == SurfaceFormat::Dxt1
         || format == SurfaceFormat::Dxt3
         || format == SurfaceFormat::Dxt5);
}

Texture::Texture(GraphicsDevice& graphicsDevice)
    : GraphicsResource { graphicsDevice }
{
}
