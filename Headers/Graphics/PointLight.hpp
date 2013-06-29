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

#ifndef POINTLIGHT_HPP
#define	POINTLIGHT_HPP

#include "Core/Color.hpp"
#include "Core/Vector3.hpp"
#include "Graphics/PointLightBase.hpp"

namespace SceneR
{
    namespace Graphics
    {
        /**
         * Represents a light source that has a specified position in space and projects its light in all directions.
         */
        class PointLight : public PointLightBase
        {
        public:
            /**
             * Initializes a new instance of the PointLight class at the origin.
             */
            PointLight();
            
            /**
             * Initializes a new instance of the PointLight class at the specified position, using the specified color.
             * @param diffuseColor the diffuse color of the light.
             * @param position The position of the light.
             */
            PointLight(const SceneR::Core::Color&   diffuseColor,
                       const SceneR::Core::Vector3& position);
            
        protected:
            /**
             * Releases all resources being used by the current PointLight
             */
            virtual ~PointLight() = default;
        };
    }
}

#endif	/* POINTLIGHT_HPP */

