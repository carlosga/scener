// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_VERTEXDECLARATION_HPP
#define SCENER_GRAPHICS_VERTEXDECLARATION_HPP

#include <cstddef>
#include <vector>

#include "scener/graphics/VertexElement.hpp"

namespace scener { namespace graphics {

/// A vertex declaration, which defines per-vertex data.
class VertexDeclaration final
{
public:
    /// Initializes a new instance of the VertexDeclaration class.
    /// \param vertexStride The number of bytes per element.
    /// \param vertexElements vertex elements.
    VertexDeclaration(std::size_t vertexStride, const std::vector<VertexElement>& vertexElements) noexcept;

public:
    /// Gets the number of bytes from one vertex to the next.
    /// \returns the stride (in bytes).
    std::size_t vertex_stride() const noexcept;

    /// Gets the vertex shader declaration.
    /// \returns the vertex elements that make up the vertex shader declaration.
    const std::vector<VertexElement>& vertex_elements() const noexcept;

private:
    std::size_t                _vertex_stride;
    std::vector<VertexElement> _vertex_elements;
};

}}

#endif // SCENER_GRAPHICS_VERTEXDECLARATION_HPP */
