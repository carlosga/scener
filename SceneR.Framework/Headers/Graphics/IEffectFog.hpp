// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the Apache License, Version 2.0. See LICENSE file in the project root for full license information.

#ifndef IEFFECTFOG_HPP
#define IEFFECTFOG_HPP

#include <System/Core.hpp>

namespace SceneR
{
    namespace Framework
    {
        struct Vector3;
    }
}

namespace SceneR
{
    namespace Graphics
    {
        /**
         * Defines fog parameters for the current effect.
         */
        class IEffectFog
        {
        public:
            /**
             * Releases all resource sbeing used by this IEffectFog instance
             */
            virtual ~IEffectFog() = default;

        public:
            /**
             *  Gets the fog color.
             */
            virtual const SceneR::Framework::Vector3& FogColor() const = 0;

            /**
             *  Set the fog color.
             */
            virtual void FogColor(const SceneR::Framework::Vector3& color) = 0;

            /**
             * Gets a value indicating whether for is enabled for the current effect.
             */
            virtual const System::Boolean& FogEnabled() const = 0;

            /**
             * Gets a value indicating whether for is enabled for the current effect.
             */
            virtual void FogEnabled(const System::Boolean& fogEnabled) = 0;

            /**
             * Gets maximum z value for fog.
             */
            virtual const System::Single& FogEnd() const = 0;

            /**
             * Sets maximum z value for fog.
             */
            virtual void FogEnd(const System::Single& fogEnd) = 0;

            /**
             * Gets minimum z value for fog.
             */
            virtual const System::Single& FogStart() const = 0;

            /**
             * Sets minimum z value for fog.
             */
            virtual void FogStart(const System::Single& fogStart) = 0;
        };
    }
}

#endif  /* IEFFECTFOG_HPP */
