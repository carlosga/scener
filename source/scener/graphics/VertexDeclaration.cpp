// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/VertexDeclaration.hpp"

namespace scener { namespace graphics {

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

}}
