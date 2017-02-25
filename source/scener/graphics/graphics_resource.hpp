// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_GRAPHICS_RESOURCE_HPP
#define SCENER_GRAPHICS_GRAPHICS_RESOURCE_HPP

#include <string>

#include <gsl/gsl>

namespace scener::graphics
{
    class graphics_device;

    /// Queries and prepares resources.
    class graphics_resource
    {
    public:
        /// Initializes a new instance of the graphics_resource class.
        /// \param device the graphics device associated to thi graphics resource.
        graphics_resource(gsl::not_null<graphics_device*> device) noexcept;

        /// Destructor
        virtual ~graphics_resource() = default;

    public:
        /// Gets the fraphics device associated with this graphics_resource.
        /// \returns The graphics device associated with this graphics_resource.
        graphics_device* device() const noexcept;

    public:
        /// Gets or sets the name of the resource.
        std::string name;

    protected:
        graphics_device* _graphics_device;
    };
}

#endif // SCENER_GRAPHICS_GRAPHICS_RESOURCE_HPP
