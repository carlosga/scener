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
            /**
             * Gets the arithmetic operation when blending alpha values.
             */
            const BlendFunction& AlphaBlendFunction() const;

            /**
             * Sets the arithmetic operation when blending alpha values.
             */
            void AlphaBlendFunction(const BlendFunction& alphaBlendFunction);

            /**
             * Gets the blend factor for the destination alpha,
             * which is the percentage of the destination alpha included in the blended result.
             */
            const Blend& AlphaDestinationBlend() const;

            /**
             * Sets the blend factor for the destination alpha,
             * which is the percentage of the destination alpha included in the blended result.
             */
            void AlphaDestinationBlend(const Blend& alphaDestinationBlend);

            /**
             * Gets the alpha blend factor.
             */
            const Blend& AlphaSourceBlend() const;

            /**
             * Sets the alpha blend factor.
             */
            void AlphaSourceBlend(const Blend& alphaSourceBlend);

            /**
             * Gets the four-component (RGBA) blend factor for alpha blending.
             */
            const SceneR::Framework::Color& BlendFactor() const;

            /**
             * Sets the four-component (RGBA) blend factor for alpha blending.
             */
            void BlendFactor(const SceneR::Framework::Color& blendFactor);

            /**
             * Gets the arithmetic operation when blending color values.
             */
            const BlendFunction& ColorBlendFunction() const;

            /**
             * Sets the arithmetic operation when blending color values.
             */
            void ColorBlendFunction(const BlendFunction& colorBlendFunction);

            /**
             * Gets the blend factor for the destination color.
             */
            const Blend& ColorDestinationBlend() const;

            /**
             * Sets the blend factor for the destination color.
             */
            void ColorDestinationBlend(const Blend& colorDestinationBlend);

            /**
             * Gets the blend factor for the source color.
             */
            const Blend& ColorSourceBlend() const;

            /**
             * Sets the blend factor for the source color.
             */
            void ColorSourceBlend(const Blend& colorSourceBlend);

            /**
             * Gets which color channels (RGBA) are enabled for writing during color blending.
             */
            const SceneR::Graphics::ColorWriteChannels& ColorWriteChannels() const;

            /**
             * Sets which color channels (RGBA) are enabled for writing during color blending.
             */
            void ColorWriteChannels(const SceneR::Graphics::ColorWriteChannels& colorWriteChannels);

            /**
             * Gets which color channels (RGBA) are enabled for writing during color blending.
             */
            const SceneR::Graphics::ColorWriteChannels& ColorWriteChannels1() const;

            /**
             * Sets which color channels (RGBA) are enabled for writing during color blending.
             */
            void ColorWriteChannels1(const SceneR::Graphics::ColorWriteChannels& colorWriteChannels1);

            /**
             * Gets which color channels (RGBA) are enabled for writing during color blending.
             */
            const SceneR::Graphics::ColorWriteChannels& ColorWriteChannels2() const;

            /**
             * Sets which color channels (RGBA) are enabled for writing during color blending.
             */
            void ColorWriteChannels2(const SceneR::Graphics::ColorWriteChannels& colorWriteChannels2);

            /**
             * Gets which color channels (RGBA) are enabled for writing during color blending.
             */
            const SceneR::Graphics::ColorWriteChannels& ColorWriteChannels3() const;

            /**
             * Sets which color channels (RGBA) are enabled for writing during color blending.
             */
            void ColorWriteChannels3(const SceneR::Graphics::ColorWriteChannels& colorWriteChannels3);

            /**
             * Gets a bitmask which defines which samples can be written during multisampling.
             */
            std::uint32_t MultiSampleMask() const;

            /**
             * Sets a bitmask which defines which samples can be written during multisampling.
             */
            void MultiSampleMask(const std::uint32_t& multiSampleMask);

        public:
            BlendState& operator=(const BlendState& blendState);

        private:
            void Apply() const;

        private:
            BlendFunction                        alphaBlendFunction;
            Blend                                alphaDestinationBlend;
            Blend                                alphaSourceBlend;
            SceneR::Framework::Color             blendFactor;
            BlendFunction                        colorBlendFunction;
            Blend                                colorDestinationBlend;
            Blend                                colorSourceBlend;
            SceneR::Graphics::ColorWriteChannels colorWriteChannels;
            SceneR::Graphics::ColorWriteChannels colorWriteChannels1;
            SceneR::Graphics::ColorWriteChannels colorWriteChannels2;
            SceneR::Graphics::ColorWriteChannels colorWriteChannels3;
            std::uint32_t                        multiSampleMask;

            friend class SceneR::Framework::GraphicsDeviceManager;
        };
    }
}

#endif /* BLENDSTATE_HPP */
