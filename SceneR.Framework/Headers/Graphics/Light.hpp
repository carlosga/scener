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

#include <Framework/Color.hpp>
#include <System/Core.hpp>

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
            * Gets the diffuse color of the light.
            * @return the diffuse color of the light.
            */
            const SceneR::Framework::Color& DiffuseColor() const;

           /**
            * Sets the diffuse color of the light.
            * @param color the diffuse color of the light.
            */
            void DiffuseColor(const SceneR::Framework::Color& diffuseColor);

            /**
             * Gets a value indicating whether the light is enabled
             */
            const System::Boolean& Enabled() const;

            /**
             * Sets a value indicating whether the light is enabled
             */
            void Enabled(const System::Boolean& enabled);

        protected:
           /**
            * Initializes a new instance of the Light class.
            */
            Light();

            /**
            * Initializes a new instance of the Light class with the given color.
            * @param color the light color.
            */
            Light(const SceneR::Framework::Color& color);

           /**
            * Default destructor
            */
            virtual ~Light();

        protected:
            System::Boolean          enabled;
            SceneR::Framework::Color diffuseColor;
        };
    }
}

#endif  /* LIGHT_HPP */
