// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef FRAMEWORK_ICOMPONENT_HPP
#define FRAMEWORK_ICOMPONENT_HPP

namespace SceneR
{
    namespace Framework
    {
        /**
         * Defines an interface for components.
         */
        class IComponent
        {
        public:
            /**
             * Releases all resources being used by this IComponent instance.
             */
            virtual ~IComponent();

        public:
            /**
             * Called when the component should be initialized.
             * This method can be used for tasks like querying for
             * services the component needs and setting up non-graphics resources.
             */
            virtual void initialize() = 0;
        };
    }
}

#endif // FRAMEWORK_ICOMPONENT_HPP
