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
            ~Viewport();

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
