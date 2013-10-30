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

#ifndef IEFFECTLIGHTS_HPP
#define IEFFECTLIGHTS_HPP

#include <System/Core.hpp>
#include <Graphics/AmbientLight.hpp>
#include <memory>
#include <vector>

namespace SceneR
{
    namespace Graphics
    {
        /**
         * Defines the lighting parameters for the current effect.
         * A basic effect implements per-vertex lighting using three directional lights.
         */
        class IEffectLights
        {
        public:
            /**
             * Releases all resource sbeing used by this IEffectsLights instance
             */
            virtual ~IEffectLights()
            {
            };

        public:
            /**
             * Gets the ambient light for the current effect
             */
            virtual const AmbientLight& GetAmbientLight() const = 0;

            /**
             * Sets the ambient light for the current effect
             */
            virtual void SetAmbientLight(const AmbientLight& ambientLight) = 0;

            /**
             * Gets the lights of the current effect
             */
            virtual const std::vector<std::shared_ptr<Light>>& GetLights() const = 0;

            /**
             * Gets the lights of the current effect
             */
            virtual void SetLights(const std::vector<std::shared_ptr<Light>> lights) const = 0;

            /**
             * Enables lighting support for the current effect.
             */
            virtual void EnableLighting() = 0;

            /**
             * Enables lighting support for the current effect.
             */
            virtual void DisableLighting() = 0;

            /**
             * Gets a value indicating wheter lighting is enabled for the current effect.
             */
            virtual const Boolean& IsLightingEnabled() = 0;

            /**
             * Enables default lighting for the current effect.
             * http://xboxforums.create.msdn.com/forums/t/25547.aspx
             * http://blogs.msdn.com/b/shawnhar/archive/2007/04/09/the-standard-lighting-rig.aspx
             */
            virtual void EnableDefaultLighting() = 0;
        };
    }
}

#endif  /* IEFFECTLIGHTS_HPP */
