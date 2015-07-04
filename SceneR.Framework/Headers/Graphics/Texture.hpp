// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <System/Core.hpp>
#include <Graphics/GraphicsResource.hpp>
#include <Graphics/SurfaceFormat.hpp>

namespace SceneR
{
    namespace Graphics
    {
        class GraphicsDevice;

        /**
         * Represents a texture reference.
         */
        class Texture : public GraphicsResource
        {
            public:
                static bool IsCompressedSurfaceFormat(const SurfaceFormat& format);

            public:
                /**
                 * @brief Initializes a new instance of the Texture class.
                 * @param graphicsDevice the graphics device.
                 */
                Texture(GraphicsDevice& graphicsDevice);

                /**
                 * Releases all resources being used by this texture.
                 */
                virtual ~Texture();

            public:
                virtual void Dispose() override = 0;

            public:
                /**
                 * Gets the format of the texture data.
                 */
                virtual const SurfaceFormat& Format() const = 0;

                /**
                 * Gets the number of texture levels in a multilevel texture.
                 */
                virtual uint32_t LevelCount() const = 0;

                /**
                 * Activates the texture object
                 */
                virtual void Activate() const = 0;

                /**
                 * Deactivates the texture object
                 */
                virtual void Deactivate() const = 0;
        };
    }
}

#endif  /* TEXTURE_HPP */
