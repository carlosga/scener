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

#ifndef MATHHELPER_HPP
#define MATHHELPER_HPP

#include <System/Core.hpp>
#include <cmath>

namespace SceneR
{
    namespace Framework
    {
        /**
         * Common math functions.
         */
        class MathHelper
        {
        public:
            /**
             * Represents the mathematical constant e.
             */
            static const System::Single& E;

            /**
             * Represents the log base ten of e.
             */
            static const System::Single& Log10E;

            /**
             * Represents the log base two of e.
             */
            static const System::Single& Log2E;

            /**
             * Represents the value of PI
             */
            static const System::Single& Pi;

            /**
             * Represents the value of PI divided by 2
             */
            static const System::Single& PiOver2;

            /**
             * Represents the value of PI divided by 4
             */
            static const System::Single& PiOver4;

            /**
             * Represents the value of pi times two.
             */
            static const System::Single& TwoPi;

        public:
            /**
             * Returns the Cartesian coordinate for one axis of a point that is defined by a given triangle and
             * two normalized barycentric (areal) coordinates.
             * @param value1 the coordinate on one axis of vertex 1 of the defining triangle.
             * @param value2 the coordinate on the same axis of vertex 2 of the defining triangle.
             * @param value3 the coordinate on the same axis of vertex 3 of the defining triangle.
             * @param amount1 the normalized barycentric (areal) coordinate b2, equal to the weighting factor for vertex 2,
             *                the coordinate of which is specified in value2.
             * @param amount2 the normalized barycentric (areal) coordinate b3, equal to the weighting factor for vertex 3,
             *                the coordinate of which is specified in value3.
             */
            static System::Single Barycentric(const System::Single& value1,
                                              const System::Single& value2,
                                              const System::Single& value3,
                                              const System::Single& amount1,
                                              const System::Single& amount2);

            /**
             * Performs a Catmull-Rom interpolation using the specified positions.
             * @param value1 the first position in the interpolation.
             * @param value2 the second position in the interpolation.
             * @param value3 the third position in the interpolation.
             * @param value4 the fourth position in the interpolation.
             * @param amount weighting factor.
             */
            static System::Single CatmullRom(const System::Single& value1,
                                             const System::Single& value2,
                                             const System::Single& value3,
                                             const System::Single& value4,
                                             const System::Single& amount);

            /**
             * Restricts a value to be within a specified range.
             * @params value the value to clamp.
             * @param min the min value.
             * @param max the max value.
             */
            static System::Single Clamp(const System::Single& value,
                                        const System::Single& min,
                                        const System::Single& max);

            /**
             * Calculates a hermite spline interpolation.
             * @param value1 source position 1.
             * @param tangent1 source tangent 1.
             * @param value2 source position 2.
             * @param tangent2 source tangent 2.
             * @param amount weighting factor.
             */
            static System::Single Hermite(const System::Single& value1,
                                          const System::Single& tangent1,
                                          const System::Single& value2,
                                          const System::Single& tangent2,
                                          const System::Single& amount);

            /**
             * Performs a linear interpolation between two vectors.
             * @param value1 first vector
             * @param value2 second vector
             * @param amount value between 0 and 1 indicating the weight of value2.
             * @returns the linear interpolation of the two vectors.
             */
            static System::Single Lerp(const System::Single& value1,
                                       const System::Single& value2,
                                       const System::Single& amount);

            /**
             * Interpolates between two values using a cubic equation.
             * @param value1 first vector
             * @param value2 second vector
             * @param amount weighting value.
             */
            static System::Single SmoothStep(const System::Single& value1,
                                             const System::Single& value2,
                                             const System::Single& amount);

            /**
             * Converts the given value in degrees to radians.
             * @param degrees the angle in degress.
             */
            static System::Single ToRadians(const System::Single& degrees);

            /**
             * Converts the given value in radians to degrees.
             * @param radians the angle in radians.
             */
            static System::Single ToDegrees(const System::Single& radians);

            /**
             * Reduces a given angle to a value between π and -π.
             * @param angle The angle to reduce, in radians.
             */
            static System::Single WrapAngle(const System::Single& angle);

        private:
            MathHelper() = delete;
            MathHelper(const MathHelper& helper) = delete;
            MathHelper& operator=(const MathHelper& helper) = delete;
        };
    }
}

#endif  /* MATHHELPER_HPP */
