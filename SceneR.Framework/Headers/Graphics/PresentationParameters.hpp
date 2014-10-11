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

#include <Framework/PresentInterval.hpp>

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

            /**
             * Releases all resources being used by this PesentatationParameters.
             */
            ~PresentationParameters() = default;

        public:
            /**
             * Gets a value indicating whether an application is running in a full screen mode.
             */
            const System::Boolean& FullScreen() const;

            /**
             * Sets a value indicating whether an application is running in a full screen mode.
             */
            void FullScreen(const System::Boolean& fullScreen);

            /**
             * Gets the height of a swap chain's back buffers, in pixels.
             */
            const System::Size& BackBufferHeight() const;

            /**
             * Sets the height of a swap chain's back buffers, in pixels.
             */
            void BackBufferHeight(const System::Size& backBufferHeight);

            /**
             * Gets the width of a swap chain's back buffers, in pixels.
             */
            const System::Size& BackBufferWidth() const;

            /**
             * Gets the width of a swap chain's back buffers, in pixels.
             */
            void BackBufferWidth(const System::Size& backBufferWidth);

            /**
             * Gets the number of sample locations during multisampling.
             */
            const System::Size& MultiSampleCount() const;

            /**
             * Sets the number of sample locations during multisampling.
             */
            void MultiSampleCount(const System::Size& multiSampleCount);

            /**
             * Gets the swap buffer interval.
             */
            const SceneR::Framework::PresentInterval& PresentInterval() const;

            /**
             * Sets the swap buffer interval.
             */
            void PresentInterval(const SceneR::Framework::PresentInterval& presentInterval);

        private:
            System::Boolean                    fullScreen;
            System::Size                       backBufferHeight;
            System::Size                       backBufferWidth;
            System::Size                       multiSampleCount;
            SceneR::Framework::PresentInterval presentInterval;
        };
    }
}

#endif  /* PRESENTATIONPARAMETERS_HPP */
