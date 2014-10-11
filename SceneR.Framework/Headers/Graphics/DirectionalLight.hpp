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

#include <Framework/Vector3.hpp>

namespace SceneR
{
    namespace Graphics
    {
        /**
         * Light object that projects its effect along a direction specified by a Vector3.
         */
        class DirectionalLight
        {
        public:
            /**
             * Creates an instance of a light that projects its effect in a specified direction.
             * This contructor creates an instance of a white light projected along a Vector3 of value (0, 0, -1).
             */
            DirectionalLight();

            /**
             * Creates an instance of a light that projects its effect along a specified Vector3 with a specified color.
             * @param diffuseColor diffuse color of the new light.
             * @param direction the direction of the new light.
             * @param enabled a value indicating whether the light is enabled..
             * @param specularColor specular color of the new light.
             */
            DirectionalLight(const SceneR::Framework::Vector3& diffuseColor
                           , const SceneR::Framework::Vector3& direction
                           , const System::Boolean&            enabled
                           , const SceneR::Framework::Vector3& specularColor);


            /**
             * Releases all resources being used by this DirectionalLight.
             */
            ~DirectionalLight() = default;

        public:
            /**
             * Gets the diffuse color of the light.
             * @return the diffuse color of the light.
             */
             const SceneR::Framework::Vector3& DiffuseColor() const;

            /**
             * Sets the diffuse color of the light.
             * @param color the diffuse color of the light.
             */
             void DiffuseColor(const SceneR::Framework::Vector3& diffuseColor);

            /**
             * Gets the vector along which the light's effect will be seen on models in a 3-D scene.
             * @return the vector along which the light's effect will be seen on models in a 3-D scene.
             */
            const SceneR::Framework::Vector3& Direction() const;

            /**
             * Sets the vector along which the light's effect will be seen on models in a 3-D scene.
             */
            void Direction(const SceneR::Framework::Vector3& direction);

            /**
             * Gets a value indicating wheter the light is enabled.
             * @return true if the light is enabled; otherwise false.
             */
            const System::Boolean& Enabled() const;

            /**
             * Sets a value indicating wheter the light is enabled.
             */
            void Enabled(const System::Boolean& enabled);

            /**
             * Gets the specular color of the light.
             * @return the specular color of the light.
             */
             const SceneR::Framework::Vector3& SpecularColor() const;

            /**
             * Sets the specular color of the light.
             * @param color the specular color of the light.
             */
             void SpecularColor(const SceneR::Framework::Vector3& specularColor);

        private:
            SceneR::Framework::Vector3 diffuseColor;
            SceneR::Framework::Vector3 direction;
            System::Boolean            enabled;
            SceneR::Framework::Vector3 specularColor;
        };
    }
}

#endif  /* DIRECTIONALLIGHT_HPP */
