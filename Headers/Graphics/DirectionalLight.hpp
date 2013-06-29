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

#ifndef DIRECTIONALLIGHT_HPP
#define DIRECTIONALLIGHT_HPP

#include "Core/Core.hpp"
#include "Core/Vector3.hpp"
#include "Graphics/Light.hpp"

namespace SceneR
{
    namespace Graphics
    {
        /**
         * Light object that projects its effect along a direction specified by a Vector3.
         */
        class DirectionalLight : public Light
        {
        public:
            /**
             * Creates an instance of a light that projects its effect in a specified direction.
             * This contructor creates an instance of a white light projected along a Vector3 of value (0,0,-1).
             */
            DirectionalLight();
            
            /**
             * Creates an instance of a light that projects its effect along a specified Vector3 with a specified color.
             * @param diffuseColor diffuse color of the new light.
             * @param direction the direction of the new light.
             */
            DirectionalLight(const SceneR::Core::Color& diffuseColor,
                             const SceneR::Core::Vector3& direction);

        public:
            /**
             * Gets the vector along which the light's effect will be seen on models in a 3-D scene.
             * @return the vector along which the light's effect will be seen on models in a 3-D scene.
             */
            const SceneR::Core::Vector3& GetDirection() const;

            /**
             * Sets the vector along which the light's effect will be seen on models in a 3-D scene.
             */
            void SetDirection(const SceneR::Core::Vector3& direction);
            
        private:
            /**
             * Represents the vector along which the light's effect will be seen on models in a 3-D scene.
             */
            SceneR::Core::Vector3 direction;
        };
    }
}

#endif  /* DIRECTIONALLIGHT_HPP */
