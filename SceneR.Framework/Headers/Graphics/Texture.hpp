// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef GRAPHICS_TEXTURE_HPP
#define GRAPHICS_TEXTURE_HPP

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
            static bool is_compressed_surface_format(const SurfaceFormat& format) noexcept;

        public:
            /**
             * @brief Initializes a new instance of the Texture class.
             * @param graphicsDevice the graphics device.
             */
            Texture(gsl::not_null<GraphicsDevice*> graphicsDevice) noexcept;

            /**
             * Releases all resources being used by this texture.
             */
            virtual ~Texture() override = default;

        public:
            virtual void dispose() override = 0;

        public:
            /**
             * Gets the texture identifier
             */
            virtual std::uint32_t id() const noexcept = 0;

            /**
             * Gets the format of the texture data.
             */
            virtual const SurfaceFormat& format() const noexcept = 0;

            /**
             * Gets the number of texture levels in a multilevel texture.
             */
            virtual std::size_t level_count() const noexcept = 0;

            /**
             * Activates the texture object
             */
            virtual void bind() const = 0;

            /**
             * Deactivates the texture object
             */
            virtual void unbind() const = 0;
        };
    }
}

#endif  // GRAPHICS_TEXTURE_HPP
