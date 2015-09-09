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
        class SamplersReader;
    }
}

namespace SceneR
{
    namespace Graphics
    {
        class BasicEffect;
        class GraphicsDevice;
        class SkinnedEffect;

        /**
         * Contains sampler state, which determines how to sample texture data.
         */
        class SamplerState: public GraphicsResource
        {
        public:
            /**
             * Initializes a new instance of the SamplerState class.
             */
            SamplerState(GraphicsDevice& graphicsDevice);

            /**
             * @brief Copy constructor.
             * @param samplerState The sampler state to copy from.
             */
            SamplerState(const SamplerState& samplerState);

            /**
             * Destructor
             */
            ~SamplerState();

        public:
            void dispose() override;

        public:
            SamplerState& operator=(const SamplerState& samplerState);

        private:
            void apply(const std::uint32_t& textureId) const;
            void get_min_max_filters(GLenum& minfilter, GLenum& magfilter) const;

        private:
            /**
             * Gets or sets the texture-address mode for the u-coordinate.
             */
            TextureAddressMode address_U;

            /**
             * Gets or sets the texture-address mode for the v-coordinate.
             */
            TextureAddressMode address_V;

            /**
             * Gets or sets the texture-address mode for the w-coordinate.
             */
            TextureAddressMode address_W;

            /**
             * Gets or sets the type of filtering during sampling.
             */
            TextureFilter mag_filter;

            /**
             * Gets or sets the type of filtering during sampling.
             */
            TextureFilter min_filter;

            /**
             * Gets or sets the maximum anisotropy. The default value is 0.
             */
            std::int32_t max_anisotropy;

            /**
             * Gets or sets the level of detail (LOD) index of the largest map to use.
             */
            std::size_t max_mip_level;

            /**
             * Gets or sets the mipmap LOD bias, which ranges from -1.0 to +1.0. The default value is 0.
             */
            float mip_map_level_of_detail_bias;

            friend class SceneR::Content::SamplersReader;
        };
    }
}

#endif  // GRAPHICS_SAMPLERSTATE_HPP
