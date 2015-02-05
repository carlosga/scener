// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <Graphics/SurfaceFormat.hpp>
#include <Graphics/GraphicsResource.hpp>

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
                static System::Boolean IsCompressedSurfaceFormat(const SurfaceFormat& format);

            public:
                /**
                 * Releases all resources being used by this texture.
                 */
                virtual ~Texture() = default;

            public:
                /**
                 * Gets the format of the texture data.
                 */
                virtual const SurfaceFormat& Format() const = 0;

                /**
                 * Gets the number of texture levels in a multilevel texture.
                 */
                virtual const System::UInt32& LevelCount() const = 0;

            public:
                /**
                 * Activates the texture object
                 */
                virtual void Activate() = 0;

                /**
                 * Deactivates the texture object
                 */
                virtual void Deactivate() = 0;

            protected:
                Texture(GraphicsDevice& graphicsDevice);
        };
    }
}

#endif  /* TEXTURE_HPP */
