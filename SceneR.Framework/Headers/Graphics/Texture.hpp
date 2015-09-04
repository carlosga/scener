// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <cstddef>

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
            static bool is_compressed_surface_format(const SurfaceFormat& format);

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
            virtual void dispose() override = 0;

        public:
            /**
             * Gets the texture identifier
             */
            virtual std::uint32_t id() const = 0;

            /**
             * Gets the format of the texture data.
             */
            virtual const SurfaceFormat& format() const = 0;

            /**
             * Gets the number of texture levels in a multilevel texture.
             */
            virtual std::size_t level_count() const = 0;

            /**
             * Activates the texture object
             */
            virtual void activate() const = 0;

            /**
             * Deactivates the texture object
             */
            virtual void deactivate() const = 0;
        };
    }
}

#endif  /* TEXTURE_HPP */
