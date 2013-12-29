//-------------------------------------------------------------------------------
//Copyright 2013 Carlos Guzmán Álvarez
//
//Licensed under the Apache License, Version 2.0 (the "License");
//you may not use this file except in compliance with the License.
//You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//Unless required by applicable law or agreed to in writing, software
//distributed under the License is distributed on an "AS IS" BASIS,
//WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//See the License for the specific language governing permissions and
//limitations under the License.
//-------------------------------------------------------------------------------

#ifndef BLENDSTATE_HPP
#define BLENDSTATE_HPP

#include <Framework/Color.hpp>
#include <Graphics/Blend.hpp>
#include <Graphics/BlendFunction.hpp>
#include <Graphics/ColorWriteChannels.hpp>
#include <Graphics/GraphicsResource.hpp>
#include <System/Core.hpp>

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
        class BlendState: public SceneR::Graphics::GraphicsResource
        {
        public:
//            /**
//             * A built-in state object with settings for additive blend, that is adding the destination data to the source data without using alpha.
//             */
//            static const BlendState& Additive;
//
//            /**
//             *  A built-in state object with settings for alpha blend, that is blending the source and destination data using alpha.
//             */
//            static const BlendState& AlphaBlend;
//
//            /**
//             * A built-in state object with settings for blending with non-premultipled alpha,
//             * that is blending source and destination data using alpha while assuming the color
//             * data contains no alpha information.
//             */
//            static const BlendState& NonPremultiplied;
//
//            /**
//             * A built-in state object with settings for opaque blend, that is overwriting the source with the destination data.
//             */
//            static const BlendState& Opaque;

        public:
            /**
             * Initializes a new instance of the BlendState class.
             */
            BlendState(GraphicsDevice& graphicsDevice);

            /**
             * Releases all resources being used by this BlendState.
             */
            virtual ~BlendState();

        public:
            const BlendFunction& AlphaBlendFunction() const;

            void AlphaBlendFunction(const BlendFunction& alphaBlendFunction);

            const Blend& AlphaDestinationBlend() const;

            void AlphaDestinationBlend(const Blend& alphaDestinationBlend);

            const Blend& AlphaSourceBlend() const;

            void AlphaSourceBlend(const Blend& alphaSourceBlend);

            const SceneR::Framework::Color& BlendFactor() const;

            void BlendFactor(const SceneR::Framework::Color& blendFactor);

            const BlendFunction& ColorBlendFunction() const;

            void ColorBlendFunction(const BlendFunction& colorBlendFunction);

            const Blend& ColorDestinationBlend() const;

            void ColorDestinationBlend(const Blend& colorDestinationBlend);

            const Blend& ColorSourceBlend() const;

            void ColorSourceBlend(const Blend& colorSourceBlend);

            const SceneR::Graphics::ColorWriteChannels& ColorWriteChannels() const;

            void ColorWriteChannels(const SceneR::Graphics::ColorWriteChannels& colorWriteChannels);

            const SceneR::Graphics::ColorWriteChannels& ColorWriteChannels1() const;

            void ColorWriteChannels1(const SceneR::Graphics::ColorWriteChannels& colorWriteChannels1);

            const SceneR::Graphics::ColorWriteChannels& ColorWriteChannels2() const;

            void ColorWriteChannels2(const SceneR::Graphics::ColorWriteChannels& colorWriteChannels2);

            const SceneR::Graphics::ColorWriteChannels& ColorWriteChannels3() const;

            void ColorWriteChannels3(const SceneR::Graphics::ColorWriteChannels& colorWriteChannels3);

            const System::UInt32& MultiSampleMask() const;

            void MultiSampleMask(const System::UInt32& multiSampleMask);

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
            System::UInt32                       multiSampleMask;

            friend class SceneR::Framework::GraphicsDeviceManager;
        };
    }
}

#endif /* BLENDSTATE_HPP */
