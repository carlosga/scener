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

#ifndef IEFFECTFOG_HPP
#define IEFFECTFOG_HPP

#include "Core/Color.hpp"

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
            virtual ~IEffectFog()
            {
            };

        public:
            /**
             *  Gets the fog color.
             */
            virtual const SceneR::Core::Color& GetFogColor() const = 0;

            /**
             *  Set the fog color.
             */
            virtual void SetFogColor(const SceneR::Core::Color& color) = 0;

            /**
             * Enables fog for the current effect.
             */
            virtual void EnableFog() = 0;

            /**
             * Disables fog for the current effect.
             */
            virtual void DisableFog() = 0;

            /**
             * Gets a value indicating whether for is enabled for the current effect.
             */
            virtual const Boolean& IsFogEnabled() const = 0;

            /**
             * Gets maximum z value for fog.
             */
            virtual const Single& GetFogEnd() const = 0;

            /**
             * Sets maximum z value for fog.
             */
            virtual void SetFogEnd(const Single& fogEnd) = 0;

            /**
             * Gets minimum z value for fog.
             */
            virtual const Single& GetFogStart() const = 0;

            /**
             * Sets minimum z value for fog.
             */
            virtual void SetFogStart(const Single& fogStart) = 0;
        };
    }
}

#endif  /* IEFFECTFOG_HPP */
