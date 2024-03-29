// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_ICOMPONENT_HPP
#define SCENER_GRAPHICS_ICOMPONENT_HPP

namespace scener::graphics
{
    /// Defines an interface for components.
    class icomponent
    {
    public:
        /// Virtual destructor.
        virtual ~icomponent() = default;

    public:
        /// Called when the component should be initialized.
        /// This method can be used for tasks like querying for services the component needs
        /// and setting up non-graphics resources.
        virtual void initialize() noexcept = 0;
    };
}

#endif // SCENER_GRAPHICS_ICOMPONENT_HPP
