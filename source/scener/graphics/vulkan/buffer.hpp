// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_VULKAN_BUFFER_HPP
#define SCENER_GRAPHICS_VULKAN_BUFFER_HPP

#include <gsl/gsl>
#include <vulkan/vulkan.hpp>

#include "scener/graphics/vulkan/buffer_usage.hpp"
#include "scener/graphics/vulkan/vulkan_memory_allocator.hpp"

namespace scener::graphics::vulkan
{
    struct buffer_resources
    {
    public:
        vk::Buffer        memory_buffer;
        VmaAllocation     memory_buffer_allocation;
        VmaAllocationInfo memory_buffer_allocation_info;
    };

    /// Represents a Vulkan buffer object.
    class buffer final
    {
    public:
        /// Initializes a new instance of the Buffer class.
        /// \param usage the buffer usage.
        /// \param size the buffer size.
        /// \param buffer the vulkan buffer.
        buffer(buffer_usage usage, vk::SharingMode sharing_mode, std::uint64_t count, VmaAllocator* allocator) noexcept;

        ~buffer();

    public:
        const std::vector<buffer_resources>& buffers() const noexcept;

        std::uint64_t size() const noexcept;

        /// Gets the buffer usage.
        buffer_usage usage() const noexcept;

        /// Gets a subset of data from a buffer object's data store.
        /// \param offset specifies the offset into the buffer object's data store where data replacement will begin, measured in bytes.
        /// \param count specifies the size in bytes of the data store to be obtained.
        std::vector<std::uint8_t> get_data([[maybe_unused]] std::uint64_t offset, [[maybe_unused]] std::uint64_t count) const noexcept;

        /// Creates and initializes the buffer object data store.
        /// \param data specifies a span of data that will be copied into the data store for initialization.
        void set_data([[maybe_unused]] std::uint64_t offset
                    , [[maybe_unused]] std::uint64_t count
                    , [[maybe_unused]] gsl::not_null<const void*> data) const noexcept;

    private:
        buffer_usage                  _usage;
        vk::SharingMode               _sharing_mode;
        std::uint64_t                 _size;
        std::vector<buffer_resources> _buffers;
        VmaAllocator*                 _allocator;
    };
}

#endif // SCENER_GRAPHICS_VULKAN_BUFFER_HPP
