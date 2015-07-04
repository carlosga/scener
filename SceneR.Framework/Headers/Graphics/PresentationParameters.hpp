// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef PRESENTATIONPARAMETERS_HPP
#define PRESENTATIONPARAMETERS_HPP

#include <System/Core.hpp>
#include <Framework/PresentInterval.hpp>

namespace SceneR
{
    namespace Graphics
    {
        /**
         * http://msdn.microsoft.com/en-us/library/windows/desktop/ms885051.aspx
         */
        class PresentationParameters final
        {
        public:
            /**
             * Initializes a new instance of the PresentationParameters class.
             */
            PresentationParameters();

            /**
             * @brief Copy constructor.
             * @param parameters the presentation parameters to copy from.
             */
            PresentationParameters(const PresentationParameters& parameters);

            /**
             * Releases all resources being used by this PesentatationParameters.
             */
            ~PresentationParameters();

        public:
            /**
             * Gets a value indicating whether an application is running in a full screen mode.
             */
            bool FullScreen() const;

            /**
             * Sets a value indicating whether an application is running in a full screen mode.
             */
            void FullScreen(const bool& fullScreen);

            /**
             * Gets the height of a swap chain's back buffers, in pixels.
             */
            uint32_t BackBufferHeight() const;

            /**
             * Sets the height of a swap chain's back buffers, in pixels.
             */
            void BackBufferHeight(const uint32_t& backBufferHeight);

            /**
             * Gets the width of a swap chain's back buffers, in pixels.
             */
            uint32_t BackBufferWidth() const;

            /**
             * Gets the width of a swap chain's back buffers, in pixels.
             */
            void BackBufferWidth(const uint32_t& backBufferWidth);

            /**
             * Gets the number of sample locations during multisampling.
             */
            uint32_t MultiSampleCount() const;

            /**
             * Sets the number of sample locations during multisampling.
             */
            void MultiSampleCount(const uint32_t& multiSampleCount);

            /**
             * Gets the swap buffer interval.
             */
            const SceneR::Framework::PresentInterval& PresentInterval() const;

            /**
             * Sets the swap buffer interval.
             */
            void PresentInterval(const SceneR::Framework::PresentInterval& presentInterval);

        public:
            PresentationParameters& operator=(const PresentationParameters& parameters);

        private:
            bool                               fullScreen;
            uint32_t                           backBufferHeight;
            uint32_t                           backBufferWidth;
            uint32_t                           multiSampleCount;
            SceneR::Framework::PresentInterval presentInterval;
        };
    }
}

#endif  /* PRESENTATIONPARAMETERS_HPP */
