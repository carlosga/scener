// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/VertexElement.hpp>

namespace SceneR
{
    namespace Graphics
    {
        VertexElement::VertexElement(const std::size_t&         offset
                                   , const VertexElementFormat& vertexElementFormat
                                   , const VertexElementUsage&  vertexElementUsage
                                   , const std::uint32_t&       usageIndex)
            : _offset                { offset }
            , _vertex_element_format { vertexElementFormat }
            , _vertex_element_usage  { vertexElementUsage }
            , _usage_index           { usageIndex }
        {
        }

        std::size_t VertexElement::offset() const
        {
            return _offset;
        }

        std::uint32_t VertexElement::usage_index() const
        {
            return _usage_index;
        }

        const SceneR::Graphics::VertexElementFormat& VertexElement::vertex_element_format() const
        {
            return _vertex_element_format;
        }

        const SceneR::Graphics::VertexElementUsage& VertexElement::vertex_element_usage() const
        {
            return _vertex_element_usage;
        }
    }
}
