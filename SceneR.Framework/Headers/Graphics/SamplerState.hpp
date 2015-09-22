// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef GRAPHICS_SAMPLERSTATE_HPP
#define GRAPHICS_SAMPLERSTATE_HPP

#include <cstddef>
#include <cstdint>

#include <Graphics/TextureFilter.hpp>
#include <Graphics/TextureTarget.hpp>
#include <Graphics/TextureAddressMode.hpp>
#include <Graphics/GraphicsResource.hpp>

namespace SceneR
{
    namespace Content
    {
        template <typename T> class ContentTypeReader;
    }

    namespace Graphics
    {
        /**
         * Contains sampler state, which determines how to sample texture data.
         */
        class SamplerState: public GraphicsResource
        {
        public:
            /**
             * Initializes a new instance of the SamplerState class.
             */
            SamplerState(GraphicsDevice* graphicsDevice);

            /**
             * @brief Copy constructor.
             * @param samplerState The sampler state to copy from.
             */
            SamplerState(const SamplerState& samplerState) = default;

            /**
             * Destructor
             */
            ~SamplerState() = default;

        public:
            void dispose() override;

        public:
            SamplerState& operator=(const SamplerState& samplerState) = default;

        private:
            void apply(const std::uint32_t& textureId) const;
            void get_min_max_filters(GLenum& minfilter, GLenum& magfilter) const;

        public:
            /**
             * Gets or sets the texture-address mode for the u-coordinate.
             */
            TextureAddressMode address_U = { TextureAddressMode::Wrap };

            /**
             * Gets or sets the texture-address mode for the v-coordinate.
             */
            TextureAddressMode address_V = { TextureAddressMode::Wrap };

            /**
             * Gets or sets the texture-address mode for the w-coordinate.
             */
            TextureAddressMode address_W = { TextureAddressMode::Wrap };

            /**
             * Gets or sets the type of filtering during sampling.
             */
            TextureFilter mag_filter = { TextureFilter::Linear };

            /**
             * Gets or sets the type of filtering during sampling.
             */
            TextureFilter min_filter = { TextureFilter::Linear };

            /**
             * Gets or sets the maximum anisotropy. The default value is 0.
             */
            std::int32_t max_anisotropy = 4;

            /**
             * Gets or sets the level of detail (LOD) index of the largest map to use.
             */
            std::size_t max_mip_level = 0;

            /**
             * Gets or sets the mipmap LOD bias, which ranges from -1.0 to +1.0. The default value is 0.
             */
            float mip_map_level_of_detail_bias = 0;

            template <typename T> friend class SceneR::Content::ContentTypeReader;
        };
    }
}

#endif  // GRAPHICS_SAMPLERSTATE_HPP
