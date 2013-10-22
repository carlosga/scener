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

#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "Core/Core.hpp"
#include "Core/Color.hpp"

namespace SceneR
{
    namespace Graphics
    {
       /**
        * Object that represents lighting applied to a 3-D scene.
        */
        class Light
        {
        public:
           /**
            * Gets the color of the light.
            * @return the color of the light.
            */
            const SceneR::Core::Color& GetColor() const;

           /**
            * Sets the color of the light.
            * @param color the color of the light.
            */
            void SetColor(const SceneR::Core::Color& color);
        
        protected:
           /**
            * Initializes a new instance of the Light class.
            */
            Light();

            /**
            * Initializes a new instance of the Light class with the given color.
            * @param color the light color.
            */
            Light(const SceneR::Core::Color& color);

           /**
            * Default destructor
            */
            virtual ~Light();

        protected:
            UInt32              object;
            SceneR::Core::Color color;
        };
    }
}

#endif  /* LIGHT_HPP */