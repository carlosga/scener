// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_VERTEXELEMENT_HPP
#define SCENER_GRAPHICS_VERTEXELEMENT_HPP

#include <cstddef>
#include <cstdint>

#include "SceneR/Graphics/VertexElementFormat.hpp"
#include "SceneR/Graphics/VertexElementUsage.hpp"

namespace SceneR { namespace Graphics {

/**
 * Defines input vertex data to the pipeline.
 */
struct VertexElement final
{
public:
    /// Initializes a new instance of the vertex element class
    /// \param offset offset (if any) from the beginning of the stream to the beginning of the vertex data.
    /// \param vertexElementFormat one of several predefined types that define the vertex data size.
    /// \param vertexElementUsage the intended use of the vertex data.
    /// \param usageIndex modifies the usage data to allow the user to specify multiple usage types.
    VertexElement(std::size_t         offset
                , VertexElementFormat vertexElementFormat
                , VertexElementUsage  vertexElementUsage
                , std::uint32_t       usageIndex) noexcept;

public:
    /// Gets the offset (if any) from the beginning of the stream to the beginning of the vertex data.
    /// \returns offset, in bytes, to the start of the vertex data.
    std::size_t offset() const noexcept;

    /// Gets the usage data to allow the user to specify multiple usage types.
    /// \returns the usage index.
    std::uint32_t usage_index() const noexcept;

    /// Gets the format of this vertex element.
    /// \returns the format of this vertex element.
    VertexElementFormat vertex_element_format() const noexcept;

    /// Gets a value describing how the vertex element is to be used.
    /// \returns a value describing how the vertex element is to be used.
    VertexElementUsage vertex_element_usage() const noexcept;

private:
    std::size_t         _offset;
    VertexElementFormat _vertex_element_format;
    VertexElementUsage  _vertex_element_usage;
    std::uint32_t       _usage_index;
};

}}

#endif // SCENER_GRAPHICS_VERTEXELEMENT_HPP
