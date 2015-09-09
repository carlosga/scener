// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef FRAMEWORK_IUPDATEABLE_HPP
#define FRAMEWORK_IUPDATEABLE_HPP

#include <cstdint>

namespace SceneR
{
    namespace Framework
    {
        class RenderTime;

        /**
         * Defines an interface for a component that should be updated in Renderer.update.
         */
        class IUpdateable
        {
        public:
            /**
             * Releases all resources being used by this IUpdateable instance.
             */
            virtual ~IUpdateable();

        public:
            /**
             * Gets a value indicating whether this object is enabled.
             */
            virtual bool enabled() const = 0;

            /**
             * Gets the order in which to update this object relative to other objects.
             */
            virtual std::uint32_t update_order() const = 0;

            /**
             * Called when the component should be updated.
             */
            virtual void update(const RenderTime& renderTime) = 0;
        };
    }
}

#endif // FRAMEWORK_IUPDATEABLE_HPP
