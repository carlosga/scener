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
             * Converts the given value in degrees to radians.
             */
            static System::Single ToRadians(const System::Single& degrees);

            /**
             * Converts the given value in radians to degrees.
             */
            static System::Single ToDegrees(const System::Single& radians);

        private:
            /**
             * Default constructor
             */
            MathHelper() = default;
        };
    }
}

#endif  /* MATHHELPER_HPP */
