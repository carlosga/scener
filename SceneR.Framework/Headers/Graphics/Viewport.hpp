// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef VIEWPORT_HPP
#define VIEWPORT_HPP

#include <System/Core.hpp>

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
            Viewport(const System::Single& x    , const System::Single& y
                   , const System::Single& width, const System::Single& height);

            /**
             * Initializes a new instance of the ViewPort class
             */
            Viewport(const System::Single& x       , const System::Single& y,
                     const System::Single& width   , const System::Single& height,
                     const System::Single& minDepth, const System::Single& maxDepth);

            /**
             * Default destructor
             */
            ~Viewport() = default;

        public:
            const System::Single& X() const;

            const System::Single& Y() const;

            const System::Single& Width() const;

            const System::Single& Height() const;

            System::Single AspectRatio() const;

            const System::Single& MinDepth() const;

            void MinDepth(const System::Single& minDepth);

            const System::Single& MaxDepth() const;

            void MaxDepth(const System::Single& maxDepth);

            void Update(const System::Single& x    , const System::Single& y
                      , const System::Single& width, const System::Single& height);

            void Update(const System::Single& width, const System::Single& height);

            void Refresh() const;

        private:
            System::Single x;
            System::Single y;
            System::Single width;
            System::Single height;
            System::Single minDepth;
            System::Single maxDepth;
        };
    }
}

#endif  /* VIEWPORT_HPP */
