// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_INDEX_BUFFER_HPP
#define SCENER_GRAPHICS_INDEX_BUFFER_HPP

#include <cstddef>
#include <cstdint>
#include <vector>

#include <gsl/gsl>

#include "scener/graphics/component_type.hpp"
#include "scener/graphics/graphics_resource.hpp"
#include "scener/graphics/opengl/buffer.hpp"

namespace scener::graphics
{
    class graphics_device;

    /// Describes the rendering order of the vertices in a vertex buffer.
    class index_buffer final : public graphics_resource
    {
    public:
        /// Initializes a new instance of the IndexBuffer class.
        /// \param device the graphics device object to associate with the index buffer.
        /// \param index_element_type the type of each index.
        /// \param index_count the number of indices.
        index_buffer(gsl::not_null<graphics_device*> device
                   , component_type                  index_element_type
                   , std::size_t                     index_count) noexcept;

        /// Releases all resources being used by this IndexBuffer.
        ~index_buffer() override = default;

    public:
        /// Gets the number of indices in the buffer.
        /// \returns the number of indices.
        std::size_t index_count() const noexcept;

        /// Gets the type of each index.
        /// \returns the type of each index.
        component_type index_element_type() const noexcept;

        /// Gets the size (in bytes) of each index.
        /// \returns the size (in bytes) of each index.
        std::size_t element_size_in_bytes() const noexcept;

        /// Gets a copy of the index buffer data.
        /// \returns a copy of the index buffer data.
        std::vector<std::uint8_t> get_data() const noexcept;

        /// Gets a copy of the index buffer data, specifying the start index and number of elements.
        /// \param start_index index of the first element to get.
        /// \param element_count number of elements to get.
        /// \returns a copy of the index buffer data.
        std::vector<std::uint8_t> get_data(std::size_t start_index, std::size_t element_count) const noexcept;

        /// Sets the indices buffer data.
        /// \param data the new indices buffer data.
        void set_data(const gsl::span<const std::uint8_t>& data) const noexcept;

    private:
        void bind() const noexcept;
        void unbind() const noexcept;

    private:
        scener::graphics::opengl::buffer _buffer;
        std::size_t                      _index_count;
        component_type                   _index_element_type;

        friend class scener::graphics::graphics_device;
    };
}

#endif // SCENER_GRAPHICS_INDEX_BUFFER_HPP
