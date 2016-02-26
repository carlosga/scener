// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/opengl/VertexArrayObject.hpp"

#include <gsl_assert.h>

#include "scener/graphics/opengl/Platform.hpp"

namespace scener { namespace graphics { namespace opengl {

VertexArrayObject::VertexArrayObject() noexcept
{
    create();
}

VertexArrayObject::~VertexArrayObject() noexcept
{
    if (_id != 0)
    {
        glDeleteVertexArrays(1, &_id);
        _id = 0;
    }
}

std::uint32_t VertexArrayObject::id() const noexcept
{
    return _id;
}

void VertexArrayObject::bind() const noexcept
{
    glBindVertexArray(_id);
}

void VertexArrayObject::unbind() const noexcept
{
    glBindVertexArray(0);
}

void VertexArrayObject::declare(const vertex_declaration& declaration, std::uint32_t bindingIndex) const noexcept
{
    const auto& elements = declaration.vertex_elements();

    // ... declare vertex elements
    for (const auto& ve : elements)
    {
        auto type  = get_element_type(ve.format());
        auto count = static_cast<GLint>(get_element_count(ve.format()));
        auto index = static_cast<std::uint32_t>(ve.usage());

        if (type == GL_FLOAT)
        {
            glVertexArrayAttribFormat(_id, index, count, type, false, ve.offset());
        }
        else
        {
            glVertexArrayAttribIFormat(_id, index, count, type, ve.offset());
        }

        glEnableVertexArrayAttrib(_id, index);
        glVertexArrayAttribBinding(_id, index, bindingIndex);
    }
}

void VertexArrayObject::bind_to_buffer(const Buffer& buffer
                                     , uint32_t      bindingIndex
                                     , std::size_t   offset
                                     , std::size_t   stride) noexcept
{
    glVertexArrayVertexBuffer(_id, bindingIndex, buffer.id(), offset, stride);
}

void VertexArrayObject::create() noexcept
{
    glCreateVertexArrays(1, &_id);

    Ensures(_id > 0);
}

std::size_t VertexArrayObject::get_element_count(vertex_element_format vertexFormat) const noexcept
{
    switch (vertexFormat)
    {
        case vertex_element_format::single:
            return 1;

        case vertex_element_format::vector2:
        case vertex_element_format::short2:
        case vertex_element_format::normalized_short2:
        case vertex_element_format::half_vector2:
            return 2;

        case vertex_element_format::vector3:
            return 3;

        case vertex_element_format::vector4:
        case vertex_element_format::color:
        case vertex_element_format::byte4:
        case vertex_element_format::short4:
        case vertex_element_format::normalized_short4:
        case vertex_element_format::half_vector4:
            return 4;
    }
}

std::uint32_t VertexArrayObject::get_element_type(vertex_element_format vertexFormat) const noexcept
{
    switch (vertexFormat)
    {
        case vertex_element_format::byte4:
            return GL_UNSIGNED_BYTE;

        case vertex_element_format::short2:
        case vertex_element_format::normalized_short2:
        case vertex_element_format::half_vector2:
        case vertex_element_format::short4:
        case vertex_element_format::normalized_short4:
        case vertex_element_format::half_vector4:
            return GL_UNSIGNED_SHORT;

        case vertex_element_format::single:
        case vertex_element_format::vector2:
        case vertex_element_format::vector3:
        case vertex_element_format::vector4:
        case vertex_element_format::color:
            return GL_FLOAT;
    }
}

}}}
