// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/VertexElement.hpp>

namespace SceneR
{
    namespace Graphics
    {
        VertexElement::VertexElement(const std::size_t&                           offset
                                   , const SceneR::Graphics::VertexElementFormat& vertexElementFormat
                                   , const SceneR::Graphics::VertexElementUsage&  vertexElementUsage
                                   , const std::uint32_t&                         usageIndex)
            : _offset              { offset }
            , _vertex_element_format { vertexElementFormat }
            , _vertex_element_usage  { vertexElementUsage }
            , _usage_index           { usageIndex }
        {
        }

        VertexElement::VertexElement(const VertexElement& element)
            : _offset                { element._offset }
            , _vertex_element_format { element._vertex_element_format }
            , _vertex_element_usage  { element._vertex_element_usage }
            , _usage_index           { element._usage_index }
        {
        }

        VertexElement::~VertexElement()
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

        VertexElement& VertexElement::operator=(const VertexElement& element)
        {
            if (this != &element)
            {
                _offset                = element._offset;
                _vertex_element_format = element._vertex_element_format;
                _vertex_element_usage  = element._vertex_element_usage;
                _usage_index           = element._usage_index;
            }

            return *this;
        }
    }
}
