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

#include <System/Core.hpp>

namespace SceneR
{
    namespace Framework
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
             * @param x the x-coordinate value.
             * @param y the y-coordinate value.
             */
            Vector2(const System::Single& x, const System::Single& y);

            /**
             * Initializes a new instance of the Vector2 class (Copy constructor)
             * @param vector The Vector2 to be copied.
             */
            Vector2(const Vector2& vector);

            /**
             * Default destructor
             */
            ~Vector2() = default;

        public:
            /**
             * Gets the x-coordinate value.
             */
            const System::Single& X() const;

            /**
             * Gets the y-coordinate value.
             */
            const System::Single& Y() const;

        public:
            System::Single& operator[](const System::Int32& index);
            const System::Single& operator[](const System::Int32& index) const;

        private:
            union
            {
                System::Single coords[2];
                struct
                {
                    System::Single x;
                    System::Single y;
                };
            };
        };
    }
}

#endif  /* TEXTURECOORDINATE_HPP */
