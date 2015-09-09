// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef GRAPHICS_DISPLAYMODE_HPP
#define GRAPHICS_DISPLAYMODE_HPP

#include <cstddef>

#include <Graphics/SurfaceFormat.hpp>

struct GLFWvidmode;

namespace SceneR
{
    namespace Graphics
    {
        /**
         * Display mode information.
         */
        class DisplayMode
        {
        public:
            /**
             * Initializes a new instance of the DisplayMode class.
             */
            DisplayMode(const GLFWvidmode* mode);

            /**
             * @brief Coopy constructor
             * @param displayMode thge display mode to copy from.
             */
            DisplayMode(const DisplayMode& displayMode);

            /**
             * Destructor
             */
            ~DisplayMode();

        public:
            /**
             * Gets the aspect ratio used by the graphics device.
             */
            float aspect_ratio() const;

            /**
             * Gets a value indicating the surface format of the display mode.
             */
            const SurfaceFormat& format() const;

            /**
             * Gets a value indicating the screen height, in pixels.
             */
            std::size_t height() const;

            /**
             * Gets a value indicating the screen width, in pixels.
             */
            std::size_t width() const;

        public:
            DisplayMode& operator=(const DisplayMode& displayMode);

        private:
            float         _aspect_ratio;
            SurfaceFormat _format;
            std::size_t   _height;
            std::size_t   _width;
        };
    }
}

#endif  // GRAPHICS_DISPLAYMODE_HPP
