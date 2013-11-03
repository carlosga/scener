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

#ifndef SPOTLIGHT_HPP
#define SPOTLIGHT_HPP

#include <System/Core.hpp>
#include <Framework/Vector3.hpp>
#include <Graphics/PointLightBase.hpp>

namespace SceneR
{
    namespace Framework
    {
        class Color;
    }
}

namespace SceneR
{
    namespace Graphics
    {
        class SpotLight : public PointLightBase
        {
        public:
            /**
             * Initializes a new instance of the SpotLight class at the origin.
             */
            SpotLight();

            /**
             * Initializes a new instance of the SpotLight class using the specified color, position, direction,
             * and fallof values.
             * @param diffuseColor diffuse color of the new SpotLight.
             * @param position position of the new SpotLight.
             * @param direction direction of the new SpotLight.
             * @param falloffAngle
             * @param falloffExponent
             */
            SpotLight(const SceneR::Framework::Color&   diffuseColor,
                      const SceneR::Framework::Vector3& position,
                      const SceneR::Framework::Vector3& direction,
                      const System::Single&             falloffAngle,
                      const System::Single&             falloffExponent);

        public:
            /**
             * Gets a Vector3D that specifies the direction in which the SpotLight projects its light.
             * @return the Vector3D that specifies the direction in which the SpotLight projects its light.
             */
            const SceneR::Framework::Vector3& GetDirection() const;

            /**
             * Sets a Vector3D that specifies the direction in which the SpotLight projects its light.
             * @param direction a Vector3D that specifies the direction in which the SpotLight projects its light.
             */
            void SetDirection(const SceneR::Framework::Vector3& direction);

            const System::Single GetFalloffAngle() const;

            void SetFalloffAngle(const System::Single falloffAngle);

            const System::Single GetFalloffExponent() const;

            void SetFalloffExponent(const System::Single falloffExponent);

        private:
            SceneR::Framework::Vector3 direction;
            System::Single             falloffAngle;
            System::Single             falloffExponent;
        };
    }
}

#endif  /* SPOTLIGHT_HPP */
