// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef DISPLAYMODE_HPP
#define DISPLAYMODE_HPP

#include <Graphics/SurfaceFormat.hpp>

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
            ~DisplayMode() = default;

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
