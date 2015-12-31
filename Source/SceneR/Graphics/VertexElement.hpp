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
 * Defines input vertex data.
 */
class VertexElement final
{
public:
    /**
     * Initializes a new instance of the vertex element class
     */
    VertexElement(const std::size_t&         offset
                , const VertexElementFormat& vertexElementFormat
                , const VertexElementUsage&  vertexElementUsage
                , const std::uint32_t&       usageIndex) noexcept;

    /**
     * @brief Copy constructor
     * @param element the vertex element to copy from
     */
    VertexElement(const VertexElement& element) = default;

    /**
     * Releases all resources being used by this VertexElement.
     */
    ~VertexElement() = default;

public:
    /**
     * Gets the offset (if any) from the beginning of the stream to the beginning of the vertex data.
     */
    std::size_t offset() const noexcept;

    /**
     * Gets the usage data to allow the user to specify multiple usage types.
     */
    std::uint32_t usage_index() const noexcept;

    /**
     * Gets or sets the format of this vertex element.
     */
    const VertexElementFormat& vertex_element_format() const noexcept;

    /**
     * Gets a value describing how the vertex element is to be used.
     */
    const VertexElementUsage& vertex_element_usage() const noexcept;

public:
    VertexElement& operator=(const VertexElement& element) = default;

private:
    std::size_t         _offset;
    VertexElementFormat _vertex_element_format;
    VertexElementUsage  _vertex_element_usage;
    std::uint32_t       _usage_index;
};

}}

#endif // SCENER_GRAPHICS_VERTEXELEMENT_HPP
