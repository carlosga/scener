// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/VertexDeclaration.hpp"

namespace scener { namespace graphics {

vertex_declaration::vertex_declaration(std::size_t stride, const std::vector<vertex_element>& elements) noexcept
    : _vertex_stride   { stride }
    , _vertex_elements { elements }
{
}

std::size_t vertex_declaration::vertex_stride() const noexcept
{
    return _vertex_stride;
}

const std::vector<vertex_element>& vertex_declaration::vertex_elements() const noexcept
{
    return _vertex_elements;
}

}}
