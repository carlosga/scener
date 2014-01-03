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

#include <Graphics/DirectionalLight.hpp>
#include <System/Core.hpp>
#include <memory>

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
            virtual const SceneR::Framework::Vector3& AmbientLightColor() const = 0;

            /**
             * Gets the ambient light for the current effect
             */
            virtual void AmbientLightColor(const SceneR::Framework::Vector3& ambientLightColor) = 0;

            /**
             * Gets the first directional light
             */
            virtual const std::shared_ptr<DirectionalLight>& DirectionalLight0() const = 0;

            /**
             * Sets the first directional light
             */
            virtual void DirectionalLight0(const std::shared_ptr<DirectionalLight>& directionalLight) = 0;

            /**
             * Gets the second directional light
             */
            virtual const std::shared_ptr<DirectionalLight>& DirectionalLight1() const = 0;

            /**
             * Sets the second directional light
             */
            virtual void DirectionalLight1(const std::shared_ptr<DirectionalLight>& directionalLight) = 0;

            /**
             * Gets the third directional light
             */
            virtual const std::shared_ptr<DirectionalLight>& DirectionalLight2() const = 0;

            /**
             * Sets the third directional light
             */
            virtual void DirectionalLight2(const std::shared_ptr<DirectionalLight>& directionalLight) = 0;

            /**
             * Gets a value indicating wheter lighting is enabled for the current effect.
             */
            virtual const System::Boolean& LightingEnabled() const = 0;

            /**
             * Gets a value indicating wheter lighting is enabled for the current effect.
             */
            virtual void LightingEnabled(const System::Boolean& lightingEnabled) = 0;

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
