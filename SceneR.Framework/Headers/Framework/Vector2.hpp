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
             * Returns a Vector2 with ones in all of its components.
             */
            static const Vector2 One;

            /**
             * Returns the x unit Vector2 (1, 0).
             */
            static const Vector2 UnitX;

            /**
             * Returns the y unit Vector2 (0, 1).
             */
            static const Vector2 UnitY;

            /**
             * Returns a Vector2 with all of its components set to zero.
             */
            static const Vector2 Zero;

        public:
            /**
             * Performs a linear interpolation between two vectors.
             * @param value1 first vector
             * @param value2 second vector
             * @param amount Value between 0 and 1 indicating the weight of value2.
             * @returns the linear interpolation of the two vectors.
             */
            static Vector2 Lerp(const Vector2& value1,
                                const Vector2& value2,
                                const System::Single&  amount);

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

#endif  /* VECTOR2_HPP */
