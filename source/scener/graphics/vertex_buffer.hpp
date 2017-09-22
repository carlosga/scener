// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_VERTEX_BUFFER_HPP
#define SCENER_GRAPHICS_VERTEX_BUFFER_HPP

#include <cstddef>
#include <cstdint>
#include <vector>

#include "scener/graphics/graphics_resource.hpp"
#include "scener/graphics/vertex_declaration.hpp"
#include "scener/graphics/vulkan/buffer.hpp"

namespace scener::graphics
{
    class graphics_device;

    /// Represents a list of 3D vertices to be streamed to the graphics device.
    class vertex_buffer final : public graphics_resource
    {
    public:
        /// Initializes a new instance of the VertexBuffer class.
        /// \param device the graphics device associated with this vertex buffer.
        /// \param vertex_count the number of vertices.
        /// \param vertex_declaration the vertex declaration, which describes per-vertex data.
        vertex_buffer(gsl::not_null<graphics_device*>     device
                    , std::size_t                         vertex_count
                    , const graphics::vertex_declaration& vertex_declaration) noexcept;

    public:
        /// Gets the number of vertex for the current buffer.
        std::size_t vertex_count() const noexcept;

        /// Returns a copy of the vertex buffer data.
        std::vector<std::uint8_t> get_data() const noexcept;

        /// Gets a copy of the vertex buffer data, specifying the start index and number of elements.
        /// \param start_index index of the first element to get.
        /// \param element_count number of elements to get.
        std::vector<std::uint8_t> get_data(std::size_t start_index, std::size_t element_count) const noexcept;

        /// Sets the vertex buffer data.
        /// \param data the new vertex buffer data.
        void set_data(const gsl::span<const std::uint8_t>& data) const noexcept;

        /// Defines per-vertex data in a buffer.
        /// \returns the per vertex data definition of this VertexBuffer.
        const graphics::vertex_declaration& vertex_declaration() const noexcept;

    private:
        void bind() noexcept;
        void unbind() noexcept;

    private:
        std::uint32_t                _binding_index;
        std::size_t                  _vertex_count;
        graphics::vertex_declaration _vertex_declaration;
        vulkan::buffer               _buffer;

        friend class scener::graphics::graphics_device;
    };
}

#endif // SCENER_GRAPHICS_VERTEX_BUFFER_HPP
