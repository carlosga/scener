// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef BLENDSTATE_HPP
#define BLENDSTATE_HPP

#include <cstdint>

#include <Framework/Color.hpp>
#include <Graphics/GraphicsResource.hpp>
#include <Graphics/BlendFunction.hpp>
#include <Graphics/Blend.hpp>
#include <Graphics/ColorWriteChannels.hpp>

namespace SceneR
{
    namespace Framework
    {
        class GraphicsDeviceManager;
    }
}

namespace SceneR
{
    namespace Graphics
    {
        class GraphicsDevice;

        /**
         * Contains blend state for the device.
         */
        class BlendState final : public SceneR::Graphics::GraphicsResource
        {
        public:
            /**
             * Initializes a new instance of the BlendState class.
             */
            BlendState(GraphicsDevice& graphicsDevice);

            /**
             * @brief Copy constructor.
             * @param blendState The blend state to copy from.
             */
            BlendState(const BlendState& blendState);

            /**
             * Releases all resources being used by this BlendState.
             */
            ~BlendState() override;

        public:
            void dispose() override;

        public:
            BlendState& operator=(const BlendState& blendState);

        private:
            void apply() const;

        public:
            /**
             * Gets or sets the arithmetic operation when blending alpha values.
             */
            BlendFunction alpha_blend_function;

            /**
             * Gets or sets the blend factor for the destination alpha,
             * which is the percentage of the destination alpha included in the blended result.
             */
            Blend alpha_destination_blend;

            /**
             * Gets or sets the alpha blend factor.
             */
            Blend alpha_source_blend;

            /**
             * Gets or sets the four-component (RGBA) blend factor for alpha blending.
             */
            SceneR::Framework::Color blend_factor;

            /**
             * Gets or sets the arithmetic operation when blending color values.
             */
            BlendFunction color_blend_function;

            /**
             * Gets or sets the blend factor for the destination color.
             */
            Blend color_destination_blend;

            /**
             * Gets Sets the blend factor for the source color.
             */
            Blend color_source_blend;

            /**
             * Gets or sets which color channels (RGBA) are enabled for writing during color blending.
             */
            SceneR::Graphics::ColorWriteChannels color_write_channels;

            /**
             * Gets or setswhich color channels (RGBA) are enabled for writing during color blending.
             */
            SceneR::Graphics::ColorWriteChannels color_write_channels_1;

            /**
             * Gets or setswhich color channels (RGBA) are enabled for writing during color blending.
             */
            SceneR::Graphics::ColorWriteChannels color_write_channels_2;

            /**
             * Gets or setswhich color channels (RGBA) are enabled for writing during color blending.
             */
            SceneR::Graphics::ColorWriteChannels color_write_channels_3;

            /**
             * Gets or setsa bitmask which defines which samples can be written during multisampling.
             */
            std::uint32_t multi_sample_mask;

            friend class SceneR::Framework::GraphicsDeviceManager;
        };
    }
}

#endif /* BLENDSTATE_HPP */
