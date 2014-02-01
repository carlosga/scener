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

#ifndef DISPLAYMODE_HPP
#define DISPLAYMODE_HPP

#include <Graphics/SurfaceFormat.hpp>
#include <System/Core.hpp>

struct GLFWvidmode;

namespace SceneR
{
    namespace Graphics
    {
        class GraphicsAdapter;

        /**
         * Display mode information.
         */
        class DisplayMode
        {
        private:
            /**
             * Initializes a new instance of the DisplayMode class.
             */
            DisplayMode(const GLFWvidmode* mode);

        public:
            /**
             * Releases all resources being used by this DisplayMode.
             */
            virtual ~DisplayMode();

        public:
            /**
             * Gets the aspect ratio used by the graphics device.
             */
            const System::Single& AspectRatio() const;

            /**
             * Gets a value indicating the surface format of the display mode.
             */
            const SurfaceFormat& Format() const;

            /**
             * Gets a value indicating the screen height, in pixels.
             */
            const System::Size& Height() const;

            /**
             * Gets a value indicating the screen width, in pixels.
             */
            const System::Size& Width() const;

        private:
            System::Single aspectRatio;
            SurfaceFormat  format;
            System::Size   height;
            System::Size   width;

            friend class GraphicsAdapter;
        };
    }
}

#endif /* DISPLAYMODE_HPP */
