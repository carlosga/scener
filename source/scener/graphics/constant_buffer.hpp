// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_CONSTANT_BUFFER_HPP
#define SCENER_GRAPHICS_CONSTANT_BUFFER_HPP

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include <gsl/gsl>

#include "scener/graphics/graphics_resource.hpp"
#include "scener/graphics/vulkan/buffer.hpp"
#include "scener/graphics/vulkan/buffer_usage.hpp"

namespace scener::graphics
{
    class graphics_device;

    /// Represents an Vulkan Uniform Buffer
    class constant_buffer final : public graphics_resource
    {
    public:
        /// Initializes a new instance of the constant_buffer class.
        /// \param device the graphics device associated with this vertex buffer.
        /// \param name the name of the constant buffer.
        /// \param size the size of the constant buffer.
        constant_buffer(gsl::not_null<graphics_device*> device
                      , const std::string&              name
                      , std::uint32_t                   size) noexcept;

    public:
        /// Gets the constant buffer name
        const std::string& name() const noexcept;

        /// Gets the constant buffer binding point.
        std::uint32_t binding_point() const noexcept;

        /// Gets the constant buffer block index.
        std::uint32_t index() const noexcept;

        /// Gets the constant buffer block data size.
        std::uint32_t size() const noexcept;

        /// Gets the constant buffer underlying memory buffer
        const vulkan::buffer& memory_buffer() const noexcept;

    public:
        /// Gets the constant buffer data.
        std::vector<std::uint8_t> get_data() const noexcept;

        /// Gets a subset of the constant buffer data.
        /// \param offset specifies the offset into the constant buffer object's data store.
        /// \param count specifies the size in bytes of the data store to be obtained.
        std::vector<std::uint8_t> get_data(std::uint32_t offset, std::uint32_t count) const noexcept;

        /// Sets the constant buffer data.
        void set_data(gsl::not_null<const void*> data) noexcept;

        /// Updates a subset of the constant buffer object's data store.
        /// \param offset specifies the offset into the constant buffer object's data store where data replacement will begin, measured in bytes.
        /// \param count specifies the size in bytes of the data store region being replaced.
        /// \param data specifies a pointer to the new data that will be copied into the data store.
        void set_data(std::uint32_t offset, std::uint32_t count, gsl::not_null<const void*> data) noexcept;

     private:
        std::uint32_t  _index;
        std::uint32_t  _binding_point;
        std::uint32_t  _size;
        std::string    _name;
        vulkan::buffer _buffer;
    };
}

#endif // SCENER_GRAPHICS_CONSTANT_BUFFER_HPP
