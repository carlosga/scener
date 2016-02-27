// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/opengl/vertex_array_object.hpp"

#include <gsl_assert.h>

#include "scener/graphics/opengl/platform.hpp"

namespace scener { namespace graphics { namespace opengl {

vertex_array_object::vertex_array_object() noexcept
{
    create();
}

vertex_array_object::~vertex_array_object() noexcept
{
    if (_id != 0)
    {
        glDeleteVertexArrays(1, &_id);
        _id = 0;
    }
}

std::uint32_t vertex_array_object::id() const noexcept
{
    return _id;
}

void vertex_array_object::bind() const noexcept
{
    glBindVertexArray(_id);
}

void vertex_array_object::unbind() const noexcept
{
    glBindVertexArray(0);
}

void vertex_array_object::declare(const vertex_declaration& declaration, std::uint32_t binding_index) const noexcept
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
        glVertexArrayAttribBinding(_id, index, binding_index);
    }
}

void vertex_array_object::bind_to_buffer(const buffer& buffer
                                       , uint32_t      bindingIndex
                                       , std::size_t   offset
                                       , std::size_t   stride) noexcept
{
    glVertexArrayVertexBuffer(_id, bindingIndex, buffer.id(), offset, stride);
}

void vertex_array_object::create() noexcept
{
    glCreateVertexArrays(1, &_id);

    Ensures(_id > 0);
}

std::size_t vertex_array_object::get_element_count(vertex_element_format format) const noexcept
{
    switch (format)
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

std::uint32_t vertex_array_object::get_element_type(vertex_element_format format) const noexcept
{
    switch (format)
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
