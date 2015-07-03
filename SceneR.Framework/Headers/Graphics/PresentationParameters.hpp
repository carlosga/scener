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
            const System::UInt32& BackBufferHeight() const;

            /**
             * Sets the height of a swap chain's back buffers, in pixels.
             */
            void BackBufferHeight(const System::UInt32& backBufferHeight);

            /**
             * Gets the width of a swap chain's back buffers, in pixels.
             */
            const System::UInt32& BackBufferWidth() const;

            /**
             * Gets the width of a swap chain's back buffers, in pixels.
             */
            void BackBufferWidth(const System::UInt32& backBufferWidth);

            /**
             * Gets the number of sample locations during multisampling.
             */
            const System::UInt32& MultiSampleCount() const;

            /**
             * Sets the number of sample locations during multisampling.
             */
            void MultiSampleCount(const System::UInt32& multiSampleCount);

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
            System::UInt32                     backBufferHeight;
            System::UInt32                     backBufferWidth;
            System::UInt32                     multiSampleCount;
            SceneR::Framework::PresentInterval presentInterval;
        };
    }
}

#endif  /* PRESENTATIONPARAMETERS_HPP */
