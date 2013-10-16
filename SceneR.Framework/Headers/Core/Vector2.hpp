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

#ifndef VECTOR2_HPP
#define VECTOR2_HPP

#include "Core/Core.hpp"

namespace SceneR
{
    namespace Core
    {
        /**
         * Represents an x and y-coordinate vector.
         */
        class Vector2
        {
        public:
            /**
             * Initializes a new instance of the Vector2 class.
             */
            Vector2();

            /**
             * Initializes a new instance of the Vector2 class with the given texture coordinates.
             *
             * @param x the x-coordinate value.
             * @param y the y-coordinate value.
             */
            Vector2(const Single& x, const Single& y);

        public:
            /**
             * Gets the x-coordinate value.
             */
            const Single& X() const;

            /**
             * Gets the y-coordinate value.
             */
            const Single& Y() const;

        public:
            Single& operator[](const Int32& index);
            const Single& operator[](const Int32& index) const;

        private:
            union
            {
                Single coords[2];
                struct
                {
                    Single x;
                    Single y;
                };
            };
        };
    }
}

#endif  /* TEXTURECOORDINATE_HPP */
