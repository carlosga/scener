// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_VERTEXDECLARATION_HPP
#define SCENER_GRAPHICS_VERTEXDECLARATION_HPP

#include <cstddef>
#include <vector>

#include "scener/graphics/VertexElement.hpp"

namespace scener { namespace graphics {

/// A vertex declaration, which defines per-vertex data.
class vertex_declaration final
{
public:
    /// Initializes a new instance of the VertexDeclaration class.
    /// \param stride The number of bytes per element.
    /// \param elements vertex elements.
    vertex_declaration(std::size_t stride, const std::vector<vertex_element>& elements) noexcept;

public:
    /// Gets the number of bytes from one vertex to the next.
    /// \returns the stride (in bytes).
    std::size_t vertex_stride() const noexcept;

    /// Gets the vertex shader declaration.
    /// \returns the vertex elements that make up the vertex shader declaration.
    const std::vector<vertex_element>& vertex_elements() const noexcept;

private:
    std::size_t                 _vertex_stride;
    std::vector<vertex_element> _vertex_elements;
};

}}

#endif // SCENER_GRAPHICS_VERTEXDECLARATION_HPP */
