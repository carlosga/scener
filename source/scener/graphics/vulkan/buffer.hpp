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
    class buffer final
    {
    public:
        /// Initializes a new instance of the Buffer class.
        /// \param usage the buffer usage.
        /// \param size the buffer size.
        /// \param buffer the vulkan buffer.
        buffer(buffer_usage      usage
             , std::size_t       size
             , const vk::Buffer& staging_buffer
             , const std::any&   staging_buffer_allocation
             , const vk::Buffer& memory_buffer
             , const std::any&   memory_buffer_allocation) noexcept;

    public:
        const vk::Buffer& staging_buffer() const noexcept;
        const std::any& staging_buffer_allocation() const noexcept;

        const vk::Buffer& memory_buffer() const noexcept;
        const std::any& memory_buffer_allocation() const noexcept;

        /// Gets the buffer usage.
        buffer_usage usage() const noexcept;

        /// Gets a subset of data from a buffer object's data store.
        /// \param offset specifies the offset into the buffer object's data store where data replacement will begin, measured in bytes.
        /// \param count specifies the size in bytes of the data store to be obtained.
        std::vector<std::uint8_t> get_data(std::size_t offset, std::size_t count) const noexcept;

        /// Creates and initializes the buffer object data store.
        /// \param data specifies a span of data that will be copied into the data store for initialization.
        void set_data(const gsl::span<const std::uint8_t>& data) const noexcept;

        /// Invalidates the content of a buffer object's data store
        void invalidate() const noexcept;

        /// Invalidates a region of a buffer object's data store
        /// \param offset the offset within the buffer's data store of the start of the range to be invalidated.
        /// \param count the length of the range within the buffer's data store to be invalidated.
        void invalidate(std::size_t offset, std::size_t count) const noexcept;

    private:
        buffer_usage _usage;
        std::size_t  _size;
        vk::Buffer   _staging_buffer;
        std::any     _staging_buffer_allocation;
        vk::Buffer   _memory_buffer;
        std::any     _memory_buffer_allocation;
    };

    class buffer_deleter final
    {
    public:
        buffer_deleter() {}

        buffer_deleter(const std::any& allocator, const std::function<void(const std::any&, const buffer&)>& deleter)
            : _allocator { allocator }
            , _deleter   { deleter }
        {
        }

        void operator()(buffer* vkbuffer)
        {
            if (vkbuffer != nullptr)
            {
                _deleter(_allocator, *vkbuffer);
                delete vkbuffer;
                vkbuffer = nullptr;
            }
        }

    private:
        std::any                                            _allocator;
        std::function<void(const std::any&, const buffer&)> _deleter;
    };
}

#endif // SCENER_GRAPHICS_OPENGL_BUFFER_HPP
