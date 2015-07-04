// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef IDRAWABLE_HPP
#define IDRAWABLE_HPP

#include <stdint.h>

namespace SceneR
{
    namespace Framework
    {
        class RenderTime;

        /**
         * Defines the interface for a drawable game component.
         */
        class IDrawable
        {
        public:
            /**
             * Releases all the resources being used by this IDrawable instance.
             */
            virtual ~IDrawable();

        public:
            /**
             * Gets a value indicating whether this object is visible.
             */
            virtual bool Visible() const = 0;

            /**
             * The order in which to draw this object relative to other objects.
             */
            virtual uint32_t DrawOrder() const = 0;

            /**
             * Called when the component should be drawn.
             */
            virtual void Draw(const RenderTime& renderTime) = 0;
        };
    }
}

#endif /* IDRAWABLE_HPP */
