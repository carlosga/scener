// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_OPENGL_BUFFER_HPP
#define SCENER_GRAPHICS_OPENGL_BUFFER_HPP

#include <any>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <memory>
#include <vector>

#include <gsl/gsl>
#include <vulkan/vulkan.hpp>

#include "scener/graphics/vulkan/buffer_usage.hpp"

namespace scener::graphics::vulkan
{
    /// Represents an OpenGL buffer object.
    struct buffer final
    {
    public:
        /// Initializes a new instance of the Buffer class.
        /// \param usage the buffer usage.
        /// \param size the buffer size.
        /// \param buffer the vulkan buffer.
        buffer(buffer_usage      usage
             , std::size_t       size
             , const vk::Buffer& memory_buffer
             , const std::any&   memory_buffer_allocation) noexcept
            : _usage                     { usage }
            , _size                      { size }
            , _memory_buffer             { memory_buffer }
            , _memory_buffer_allocation  { memory_buffer_allocation }
        {
        }

    public:
        const vk::Buffer& memory_buffer() const noexcept
        {
            return _memory_buffer;
        }

        const std::any& memory_buffer_allocation() const noexcept
        {
            return _memory_buffer_allocation;
        }

        std::size_t size() const noexcept
        {
            return _size;
        }

        /// Gets the buffer usage.
        buffer_usage usage() const noexcept
        {
            return _usage;
        }

        /// Gets a subset of data from a buffer object's data store.
        /// \param offset specifies the offset into the buffer object's data store where data replacement will begin, measured in bytes.
        /// \param count specifies the size in bytes of the data store to be obtained.
        std::vector<std::uint8_t> get_data(std::size_t offset, std::size_t count) const noexcept
        {
            return {};
        }

        /// Creates and initializes the buffer object data store.
        /// \param data specifies a span of data that will be copied into the data store for initialization.
        void set_data(const gsl::span<const std::uint8_t>& data) const noexcept
        {
        }

    private:
        buffer_usage _usage;
        std::size_t  _size;
        vk::Buffer   _memory_buffer;
        std::any     _memory_buffer_allocation;
    };
}

#endif // SCENER_GRAPHICS_OPENGL_BUFFER_HPP
