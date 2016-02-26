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

void VertexArrayObject::declare(const VertexDeclaration& declaration, std::uint32_t bindingIndex) const noexcept
{
    const auto& elements = declaration.vertex_elements();

    // ... declare vertex elements
    for (const auto& ve : elements)
    {
        auto elementType  = get_element_type(ve.vertex_element_format());
        auto elementCount = get_element_count(ve.vertex_element_format());
        auto usageIndex   = static_cast<std::uint32_t>(ve.vertex_element_usage());

        if (elementType == GL_FLOAT)
        {
            glVertexArrayAttribFormat(_id, usageIndex, static_cast<GLint>(elementCount), elementType, false, ve.offset());
        }
        else
        {
            glVertexArrayAttribIFormat(_id, usageIndex, static_cast<GLint>(elementCount), elementType, ve.offset());
        }

        glEnableVertexArrayAttrib(_id, usageIndex);
        glVertexArrayAttribBinding(_id, usageIndex, bindingIndex);
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

std::size_t VertexArrayObject::get_element_count(VertexElementFormat vertexFormat) const noexcept
{
    switch (vertexFormat)
    {
        case VertexElementFormat::single:
            return 1;

        case VertexElementFormat::vector2:
        case VertexElementFormat::short2:
        case VertexElementFormat::normalized_short2:
        case VertexElementFormat::half_vector2:
            return 2;

        case VertexElementFormat::vector3:
            return 3;

        case VertexElementFormat::vector4:
        case VertexElementFormat::color:
        case VertexElementFormat::byte4:
        case VertexElementFormat::short4:
        case VertexElementFormat::normalized_short4:
        case VertexElementFormat::half_vector4:
            return 4;
    }
}

std::uint32_t VertexArrayObject::get_element_type(VertexElementFormat vertexFormat) const noexcept
{
    switch (vertexFormat)
    {
        case VertexElementFormat::byte4:
            return GL_UNSIGNED_BYTE;

        case VertexElementFormat::short2:
        case VertexElementFormat::normalized_short2:
        case VertexElementFormat::half_vector2:
        case VertexElementFormat::short4:
        case VertexElementFormat::normalized_short4:
        case VertexElementFormat::half_vector4:
            return GL_UNSIGNED_SHORT;

        case VertexElementFormat::single:
        case VertexElementFormat::vector2:
        case VertexElementFormat::vector3:
        case VertexElementFormat::vector4:
        case VertexElementFormat::color:
            return GL_FLOAT;
    }
}

}}}
