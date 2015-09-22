// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef FRAMEWORK_IDRAWABLE_HPP
#define FRAMEWORK_IDRAWABLE_HPP

#include <cstdint>

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
            virtual ~IDrawable() = default;

        public:
            /**
             * Gets a value indicating whether this object is visible.
             */
            virtual bool visible() const = 0;

            /**
             * The order in which to draw this object relative to other objects.
             */
            virtual std::uint32_t draw_order() const = 0;

            /**
             * Called when the component should be drawn.
             */
            virtual void draw(const RenderTime& renderTime) = 0;
        };
    }
}

#endif // FRAMEWORK_IDRAWABLE_HPP
