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

#ifndef VIEWPORT_HPP
#define VIEWPORT_HPP

#include "Core/Core.hpp"

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
            Viewport(Single x, Single y, Size width, Size height);

            /**
             * Initializes a new instance of the ViewPort class
             */
            Viewport(Single x       , Single y, 
                     Single width   , Single height,
                     Single minDepth, Single maxDepth);

            /**
             * Default destructor
             */
            ~Viewport();

        public:
            const Single X() const;
            const Single Y() const;
            const Single Width() const;
            const Single Height() const;
            const Single AspectRatio() const;
            const Single GetMinDepth() const;
            void SetMinDepth(const Single& minDepth);
            const Single GetMaxDepth() const;
            void SetMaxDepth(const Single& maxDepth);

            void Update(const UInt32& x, const UInt32& y, const Size& width, const Size& height);
            void Update(const Size& width, const Size& height);
            void Refresh() const;

        private:
            Single xCoordinate;
            Single yCoordinate;
            Single vWidth;
            Single vHeight;
            Single minDepth;
            Single maxDepth;
        };
    }
}

#endif  /* VIEWPORT_HPP */
