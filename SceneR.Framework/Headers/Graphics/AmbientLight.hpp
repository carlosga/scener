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

#ifndef AMBIENTLIGHT_HPP
#define AMBIENTLIGHT_HPP

#include <Graphics/Light.hpp>

namespace SceneR
{
    namespace Framework
    {
        struct Color;
    }
}

namespace SceneR
{
    namespace Graphics
    {
        /**
         * Light object that applies light to objects uniformly, regardless of their shape.
         */
        class AmbientLight : public Light
        {
        public:
            /**
             * Initializes a new instance of the AmbientLight class.
             */
            AmbientLight();

            /**
             * Initializes a new instance of the AmbientLight class with the specified color.
             * @param ambientColor Color of the new light.
             */
            AmbientLight(const SceneR::Framework::Color& ambientColor);
        };
    }
}

#endif  /* AMBIENTLIGHT_HPP */
