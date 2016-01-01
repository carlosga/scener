// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SceneR/Graphics/VertexDeclaration.hpp"

#include "SceneR/Graphics/OpenGL/Platform.hpp"

namespace SceneR { namespace Graphics {

VertexDeclaration::VertexDeclaration(std::size_t vertexStride, const std::vector<VertexElement>& vertexElements) noexcept
    : _vertex_stride   { vertexStride }
    , _vertex_elements { vertexElements }
{
}

std::size_t VertexDeclaration::vertex_stride() const noexcept
{
    return _vertex_stride;
}

const std::vector<VertexElement>& VertexDeclaration::vertex_elements() const noexcept
{
    return _vertex_elements;
}

void VertexDeclaration::declare(std::uint32_t vaoId, std::uint32_t bindingIndex​) const noexcept
{
    // ... declare vertex elements
    for (const auto& ve : _vertex_elements)
    {
        auto elementType  = get_element_type(ve.vertex_element_format());
        auto elementCount = get_element_count(ve.vertex_element_format());
        auto usageIndex   = static_cast<std::uint32_t>(ve.vertex_element_usage());

        if (elementType == GL_FLOAT)
        {
            glVertexArrayAttribFormat(vaoId, usageIndex, elementCount, elementType, false, ve.offset());
        }
        else
        {
            glVertexArrayAttribIFormat(vaoId, usageIndex, elementCount, elementType, ve.offset());
        }

        glEnableVertexArrayAttrib(vaoId, usageIndex);
        glVertexArrayAttribBinding(vaoId, usageIndex, bindingIndex​);
    }
}

std::size_t VertexDeclaration::get_element_count(VertexElementFormat vertexFormat) const noexcept
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
        default:
            return 4;
    }
}

std::uint32_t VertexDeclaration::get_element_type(VertexElementFormat vertexFormat) const noexcept
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
        default:
            return GL_FLOAT;
    }
}

}}
