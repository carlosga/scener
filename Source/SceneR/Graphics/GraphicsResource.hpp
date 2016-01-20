// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_GRAPHICSRESOURCE_HPP
#define SCENER_GRAPHICS_GRAPHICSRESOURCE_HPP

#include <string>

#include <gsl.h>

namespace SceneR { namespace Graphics {

class GraphicsDevice;

/**
 * Queries and prepares resources.
 */
class GraphicsResource
{
public:
    /**
     * Initializes a new instance of the GraphicsResource class
     * @param graphicsDevice the graphics associated to this resources
     */
    GraphicsResource(gsl::not_null<GraphicsDevice*> graphicsDevice) noexcept;

    /**
     * Destructor
     */
    virtual ~GraphicsResource() = default;

public:
    /**
     * Gets the GraphicsDevice associated with this GraphicsResource.
     * @return The GraphicsDevice associated with this GraphicsResource.
     */
    GraphicsDevice* graphics_device() const noexcept;

public:
    /**
     * Gets or sets the name of the resource.
     */
    std::string name;

protected:
    GraphicsDevice* _graphics_device;
};

}}

#endif // SCENER_GRAPHICS_GRAPHICSRESOURCE_HPP
