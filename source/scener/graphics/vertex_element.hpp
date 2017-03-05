// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_VERTEX_ELEMENT_HPP
#define SCENER_GRAPHICS_VERTEX_ELEMENT_HPP

#include <cstddef>
#include <cstdint>

#include "scener/graphics/vertex_element_format.hpp"
#include "scener/graphics/vertex_element_usage.hpp"

namespace scener::graphics
{
    /// Defines input vertex data to the pipeline.
    struct vertex_element final
    {
    public:
        /// Initializes a new instance of the vertex element class
        /// \param offset offset (if any) from the beginning of the stream to the beginning of the vertex data.
        /// \param format one of several predefined types that define the vertex data size.
        /// \param usage the intended use of the vertex data.
        /// \param usageIndex modifies the usage data to allow the user to specify multiple usage types.
        vertex_element(std::size_t           offset
                     , vertex_element_format format
                     , vertex_element_usage  usage
                     , std::uint32_t         usageIndex) noexcept;

    public:
        /// Gets the offset (if any) from the beginning of the stream to the beginning of the vertex data.
        /// \returns offset, in bytes, to the start of the vertex data.
        std::size_t offset() const noexcept;

        /// Gets the usage data to allow the user to specify multiple usage types.
        /// \returns the usage index.
        std::uint32_t usage_index() const noexcept;

        /// Gets the format of this vertex element.
        /// \returns the format of this vertex element.
        vertex_element_format format() const noexcept;

        /// Gets a value describing how the vertex element is to be used.
        /// \returns a value describing how the vertex element is to be used.
        vertex_element_usage usage() const noexcept;

    private:
        std::size_t           _offset;
        vertex_element_format _format;
        vertex_element_usage  _usage;
        std::uint32_t         _usage_index;
    };
}

#endif // SCENER_GRAPHICS_VERTEX_ELEMENT_HPP
