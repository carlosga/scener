// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef VIEWPORT_HPP
#define VIEWPORT_HPP

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
            float X() const;

            float Y() const;

            float Width() const;

            float Height() const;

            float AspectRatio() const;

            float MinDepth() const;

            void MinDepth(const float& minDepth);

            float MaxDepth() const;

            void MaxDepth(const float& maxDepth);

            void Update() const;

            void Update(const float& x    , const float& y
                      , const float& width, const float& height);

            void Update(const float& width, const float& height);

        public:
            Viewport& operator=(const Viewport& viewport);

        private:
            float x;
            float y;
            float width;
            float height;
            float minDepth;
            float maxDepth;
        };
    }
}

#endif  /* VIEWPORT_HPP */
