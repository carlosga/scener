// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/VertexDeclaration.hpp>

#include <Graphics/OpenGL/Platform.hpp>

namespace SceneR
{
    namespace Graphics
    {
        VertexDeclaration::VertexDeclaration(const std::size_t&                vertexStride
                                           , const std::vector<VertexElement>& vertexElements) noexcept
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

        void VertexDeclaration::declare(const std::uint32_t& vaoId, const std::uint32_t& bindingIndex​) const
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

        std::size_t VertexDeclaration::get_element_count(const VertexElementFormat& vertexFormat) const noexcept
        {
            switch (vertexFormat)
            {
                case VertexElementFormat::Single:
                    return 1;

                case VertexElementFormat::Vector2:
                case VertexElementFormat::Short2:
                case VertexElementFormat::NormalizedShort2:
                case VertexElementFormat::HalfVector2:
                    return 2;

                case VertexElementFormat::Vector3:
                    return 3;

                case VertexElementFormat::Vector4:
                case VertexElementFormat::Color:
                case VertexElementFormat::Byte4:
                case VertexElementFormat::Short4:
                case VertexElementFormat::NormalizedShort4:
                case VertexElementFormat::HalfVector4:
                default:
                    return 4;
            }
        }

        std::uint32_t VertexDeclaration::get_element_type(const VertexElementFormat& vertexFormat) const noexcept
        {
            switch (vertexFormat)
            {
                case VertexElementFormat::Byte4:
                    return GL_UNSIGNED_BYTE;

                case VertexElementFormat::Short2:
                case VertexElementFormat::NormalizedShort2:
                case VertexElementFormat::HalfVector2:
                case VertexElementFormat::Short4:
                case VertexElementFormat::NormalizedShort4:
                case VertexElementFormat::HalfVector4:
                    return GL_UNSIGNED_SHORT;

                case VertexElementFormat::Single:
                case VertexElementFormat::Vector2:
                case VertexElementFormat::Vector3:
                case VertexElementFormat::Vector4:
                case VertexElementFormat::Color:
                default:
                    return GL_FLOAT;
            }
        }
    }
}
