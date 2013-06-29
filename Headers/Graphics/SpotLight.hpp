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
#define	SPOTLIGHT_HPP

#include "Core/Core.hpp"
#include "Graphics/PointLightBase.hpp"

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
            SpotLight(const SceneR::Core::Color&   diffuseColor,
                      const SceneR::Core::Vector3& position,
                      const SceneR::Core::Vector3& direction,
                      const Single&                falloffAngle,
                      const Single&                falloffExponent);
					  
		public:
            /**
             * Gets a Vector3D that specifies the direction in which the SpotLight projects its light.
             * @return the Vector3D that specifies the direction in which the SpotLight projects its light.
             */
            const SceneR::Core::Vector3& GetDirection() const;

            /**
             * Sets a Vector3D that specifies the direction in which the SpotLight projects its light.
             * @param direction a Vector3D that specifies the direction in which the SpotLight projects its light.
             */
            void SetDirection(const SceneR::Core::Vector3& direction);
            
            const Single GetFalloffAngle() const;
            
            void SetFalloffAngle(const Single falloffAngle);

            const Single GetFalloffExponent() const;
            
            void SetFalloffExponent(const Single falloffExponent);
            
        private:
            SceneR::Core::Vector3 direction;
            Single                falloffAngle;
            Single                falloffExponent;
        };
	}
}

#endif	/* SPOTLIGHT_HPP */
