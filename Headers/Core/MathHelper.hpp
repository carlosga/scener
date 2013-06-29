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

#ifndef ANGLE_HPP
#define ANGLE_HPP

#include "Core/Core.hpp"

namespace SceneR
{
    namespace Core
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
            static Single ToRadians(const Single& degrees);

            /**
             * Converts the given value in radians to degrees.
             */
            static Single ToDegrees(const Single& radians);
            
        private:
            /**
             * Default constructor
             */
            MathHelper() = default;
        };
    }
}

#endif  /* ANGLE_HPP */
