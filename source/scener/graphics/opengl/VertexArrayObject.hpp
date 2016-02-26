// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_OPENGL_VERTEXARRAYOBJECT_HPP
#define SCENER_GRAPHICS_OPENGL_VERTEXARRAYOBJECT_HPP

#include <cstddef>
#include <cstdint>

#include "scener/graphics/VertexDeclaration.hpp"
#include "scener/graphics/opengl/Buffer.hpp"

namespace scener { namespace graphics { namespace opengl {

/// Represents an opengl vertex array object.
class VertexArrayObject final
{
public:
    /// Initializes a new instance of the VertexArrayObject class.
    VertexArrayObject() noexcept;

    /// Releases all resources being used by this VertexArrayObject.
    ~VertexArrayObject() noexcept;

public:
    /// Gets the vertex array object identifier.
    std::uint32_t id() const noexcept;

    /// Activates this vertex array object.
    void bind() const noexcept;

    /// Deactivates this vertex array object.
    void unbind() const noexcept;

    /// Declares the vertex format to be used on drawing operations.
    void declare(const VertexDeclaration& declaration, std::uint32_t bindingIndex) const noexcept;

    /// Binds the vertex array to the given buffer ( it should be a vertex buffer )
    /// \param buffer The buffer to bind to the vertex buffer binding point.
    /// \param bindingIndex The index of the vertex buffer binding point to which to bind the buffer.
    /// \param offset The offset of the first element of the buffer.
    /// \param stride The distance between elements within the buffer.
    void bind_to_buffer(const Buffer& buffer, std::uint32_t bindingIndex, std::size_t offset, std::size_t stride) noexcept;

private:
    void create() noexcept;
    std::size_t get_element_count(VertexElementFormat vertexFormat) const noexcept;
    std::uint32_t get_element_type(VertexElementFormat vertexFormat) const noexcept;

private:
    VertexArrayObject(const VertexArrayObject&) = delete;
    VertexArrayObject& operator=(const VertexArrayObject&) = delete;

private:
    std::uint32_t _id = 0;
};

}}}

#endif // SCENER_GRAPHICS_OPENGL_VERTEXARRAYOBJECT_HPP
