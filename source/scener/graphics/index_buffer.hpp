// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_INDEX_BUFFER_HPP
#define SCENER_GRAPHICS_INDEX_BUFFER_HPP

#include <cstddef>
#include <cstdint>
#include <memory>
#include <vector>

#include <gsl/gsl>

#include "scener/graphics/index_type.hpp"
#include "scener/graphics/graphics_resource.hpp"
#include "scener/graphics/vulkan/buffer.hpp"

namespace scener::graphics::vulkan { class logical_device; }

namespace scener::graphics
{
    class graphics_device;

    /// Describes the rendering order of the vertices in a vertex buffer.
    class index_buffer final : public graphics_resource
    {
    public:
        /// Initializes a new instance of the IndexBuffer class.
        /// \param device the graphics device object to associate with the index buffer.
        /// \param index_count the number of indices.
        index_buffer(gsl::not_null<graphics_device*> device, std::uint32_t index_count) noexcept;

        /// Initializes a new instance of the IndexBuffer class.
        /// \param device the graphics device object to associate with the index buffer.
        /// \param index_element_type the type of each index.
        /// \param index_count the number of indices.
        index_buffer(gsl::not_null<graphics_device*> device
                   , index_type                      index_element_type
                   , std::uint32_t                   index_count) noexcept;

    public:
        /// Gets the number of indices in the buffer.
        /// \returns the number of indices.
        std::uint32_t index_count() const noexcept;

        /// Gets the type of each index.
        /// \returns the type of each index.
        index_type index_element_type() const noexcept;

        /// Gets the size (in bytes) of each index.
        /// \returns the size (in bytes) of each index.
        std::uint32_t element_size_in_bytes() const noexcept;

        /// Gets a copy of the index buffer data.
        /// \returns a copy of the index buffer data.
        std::vector<std::uint8_t> get_data() const noexcept;

        /// Gets a copy of the index buffer data, specifying the start index and number of elements.
        /// \param start_index index of the first element to get.
        /// \param element_count number of elements to get.
        /// \returns a copy of the index buffer data.
        std::vector<std::uint8_t> get_data(std::uint32_t start_index, std::uint32_t element_count) const noexcept;

        /// Sets the indices buffer data.
        /// \param data the new indices buffer data.
        void set_data(const gsl::span<const std::uint8_t>& data) noexcept;

    private:
        index_type                      _index_element_type;
        std::uint32_t                   _index_count;
        std::unique_ptr<vulkan::buffer> _buffer;

        friend class scener::graphics::vulkan::logical_device;
    };
}

#endif // SCENER_GRAPHICS_INDEX_BUFFER_HPP
