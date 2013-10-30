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

#ifndef PRESENTATIONPARAMETERS_HPP
#define PRESENTATIONPARAMETERS_HPP

#include <System/Core.hpp>

namespace SceneR
{
    namespace Graphics
    {
        /**
         * http://msdn.microsoft.com/en-us/library/windows/desktop/ms885051.aspx
         */
        class PresentationParameters
        {
        public:
            /**
             * Initializes a new instance of the PresentationParameters class.
             */
            PresentationParameters();

        public:
            /**
             * Gets a value indicating whether an application is running in a full screen mode.
             */
            const Boolean GetFullScreen() const;

            /**
             * Sets a value indicating whether an application is running in a full screen mode.
             */
            void SetFullScreen(const Boolean& fullScreen);

            /**
             * Gets the height of a swap chain's back buffers, in pixels.
             */
            const Size GetBackBufferHeight() const;

            /**
             * Sets the height of a swap chain's back buffers, in pixels.
             */
            void SetBackBufferHeight(const Size& backBufferHeight);

            /**
             * Gets the width of a swap chain's back buffers, in pixels.
             */
            const Size GetBackBufferWidth() const;

            /**
             * Gets the width of a swap chain's back buffers, in pixels.
             */
            void SetBackBufferWidth(const Size& backBufferWidth);

        private:
            Boolean fullScreen;
            Size    backBufferHeight;
            Size    backBufferWidth;

            /*
            Property    Description
            BackBufferCount    Retrieves or sets the number of back buffers.
            BackBufferFormat    Retrieves or sets the format of the back buffer.
            DeviceWindow    Retrieves or sets the display window.
            DeviceWindowHandle    Retrieves or sets the display window.
            ForceNoMultiThreadedFlag    Retrieves or sets a Boolean value that indicates whether an application can use multithreading.
            FullScreenRefreshRateInHz    Retrieves or sets the rate at which the display adapter refreshes the screen.
            MultiSample    Retrieves or sets the MultiSampleType.
            MultiSampleQuality    Retrieves or sets the multisample quality level.
            PresentationInterval    Retrieves or sets the maximum rate at which the swap chain's back buffers can be presented.
            PresentFlag    Retrieves or sets the present flag.
            SwapEffect    Retrieves or sets the swap effect.
            Windowed    Boolean value that indicates whether an application is running in a windowed mode.
            */
        };
    }
}

#endif  /* PRESENTATIONPARAMETERS_HPP */
