// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SceneR/Graphics/VertexElement.hpp"

namespace SceneR
{
    namespace Graphics
    {
        VertexElement::VertexElement(const std::size_t&         offset
                                   , const VertexElementFormat& vertexElementFormat
                                   , const VertexElementUsage&  vertexElementUsage
                                   , const std::uint32_t&       usageIndex) noexcept
            : _offset                { offset }
            , _vertex_element_format { vertexElementFormat }
            , _vertex_element_usage  { vertexElementUsage }
            , _usage_index           { usageIndex }
        {
        }

        std::size_t VertexElement::offset() const noexcept
        {
            return _offset;
        }

        std::uint32_t VertexElement::usage_index() const noexcept
        {
            return _usage_index;
        }

        const VertexElementFormat& VertexElement::vertex_element_format() const noexcept
        {
            return _vertex_element_format;
        }

        const VertexElementUsage& VertexElement::vertex_element_usage() const noexcept
        {
            return _vertex_element_usage;
        }
    }
}
