// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_OPENGL_VERTEXARRAYOBJECT_HPP
#define SCENER_GRAPHICS_OPENGL_VERTEXARRAYOBJECT_HPP

#include <cstdint>

#include "SceneR/IDisposable.hpp"

namespace SceneR { namespace Graphics { namespace OpenGL {

/**
 * Represents an opengl vertex array object
 */
class VertexArrayObject final : SceneR::IDisposable
{
public:
    /**
     * Initializes a new instance of the VertexArrayObject class.
     */
    VertexArrayObject() = default;

    /**
     * Releases all resources being used by this VertexArrayObject.
     */
    ~VertexArrayObject() override = default;

public:
    void dispose() noexcept override;

public:
    /**
     * Gets the vertex array object identifier.
     */
    std::uint32_t id() const noexcept;

    /**
     * Activates this vertex array object.
     */
    void bind() const noexcept;

    /**
     * Creates the vertex array object.
     */
    void create() noexcept;

    /**
     * Deactivates this vertex array object.
     */
    void unbind() const noexcept;

private:
    std::uint32_t _id = 0;
};

}}}

#endif // SCENER_GRAPHICS_OPENGL_VERTEXARRAYOBJECT_HPP
