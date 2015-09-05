// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef IEFFECTFOG_HPP
#define IEFFECTFOG_HPP

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
            virtual ~IEffectFog();

        public:
            /**
             *  Gets the fog color.
             */
            virtual const SceneR::Framework::Vector3& fog_color() const = 0;

            /**
             *  Set the fog color.
             */
            virtual void fog_color(const SceneR::Framework::Vector3& color) = 0;

            /**
             * Gets a value indicating whether for is enabled for the current effect.
             */
            virtual bool fog_enabled() const = 0;

            /**
             * Gets a value indicating whether for is enabled for the current effect.
             */
            virtual void fog_enabled(const bool& fogEnabled) = 0;

            /**
             * Gets maximum z value for fog.
             */
            virtual float fog_end() const = 0;

            /**
             * Sets maximum z value for fog.
             */
            virtual void fog_end(const float& fogEnd) = 0;

            /**
             * Gets minimum z value for fog.
             */
            virtual float fog_start() const = 0;

            /**
             * Sets minimum z value for fog.
             */
            virtual void fog_start(const float& fogStart) = 0;
        };
    }
}

#endif  /* IEFFECTFOG_HPP */
