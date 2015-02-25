// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

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
            ~DirectionalLight();

        public:
            /**
             * Gets the diffuse color of the light.
             * @return the diffuse color of the light.
             */
             const SceneR::Framework::Vector3& DiffuseColor() const;

            /**
             * Sets the diffuse color of the light.
             * @param diffuseColor the diffuse color of the light.
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
             * @param specularColor the specular color of the light.
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
