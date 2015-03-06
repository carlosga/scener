// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef IEFFECTLIGHTS_HPP
#define IEFFECTLIGHTS_HPP

#include <memory>

#include <System/Core.hpp>
#include <Graphics/DirectionalLight.hpp>

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
            virtual ~IEffectLights();

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
            virtual const DirectionalLight& DirectionalLight0() const = 0;

            /**
             * Gets the second directional light
             */
            virtual const DirectionalLight& DirectionalLight1() const = 0;

            /**
             * Gets the third directional light
             */
            virtual const DirectionalLight& DirectionalLight2() const = 0;

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
