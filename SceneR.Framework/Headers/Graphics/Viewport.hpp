// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef GRAPHICS_VIEWPORT_HPP
#define GRAPHICS_VIEWPORT_HPP

namespace SceneR
{
    namespace Graphics
    {
        /**
         * Represents the portion of the render target to receive draw calls.
         */
        class Viewport
        {
        public:
            /**
             * Initializes a new instance of the ViewPort class
             */
            Viewport();

            /**
             * Initializes a new instance of the ViewPort class
             */
            Viewport(const float& x    , const float& y
                   , const float& width, const float& height);

            /**
             * Initializes a new instance of the ViewPort class
             */
            Viewport(const float& x       , const float& y,
                     const float& width   , const float& height,
                     const float& minDepth, const float& maxDepth);

            /**
             * @brief Copy constructor
             * @param viewport the instance to copy from
             */
            Viewport(const Viewport& viewport);

            /**
             * destructor
             */
            ~Viewport();

        public:
            float aspect_ratio() const;

            void update() const;

        public:
            Viewport& operator=(const Viewport& viewport);

        public:
            float x;
            float y;
            float width;
            float height;
            float min_depth;
            float max_depth;
        };
    }
}

#endif  // GRAPHICS_VIEWPORT_HPP
