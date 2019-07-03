// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
// ==================================================================================================

#include "scener/graphics/vulkan/buffer.hpp"

#define VMA_IMPLEMENTATION
#include <vk_mem_alloc.h>

namespace scener::graphics::vulkan
{
    buffer::buffer(buffer_usage usage, vk::SharingMode sharing_mode, const gsl::span<const std::uint8_t>& data, VmaAllocator_T* allocator) noexcept
        : _usage                     { usage }
        , _sharing_mode              { sharing_mode }
        , _size                      { 0 }
        , _memory_buffer             { }
        , _memory_buffer_allocation  { }
        , _allocator                 { allocator }
    {
        VkBufferCreateInfo buffer_create_info = {
            VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO        // VkStructureType
          , nullptr                                     // pNext
          , 0                                           // flags
          , static_cast<std::uint64_t>(data.size())     // size
          , VK_BUFFER_USAGE_TRANSFER_SRC_BIT            // usage
          , static_cast<VkSharingMode>(sharing_mode)    // sharingMode
          , 0                                           // queueFamilyIndexCount
          , nullptr                                     // pQueueFamilyIndices
        };

        VmaAllocationCreateInfo allocation_create_info = { };

        allocation_create_info.usage = VMA_MEMORY_USAGE_CPU_ONLY;
        allocation_create_info.flags = VMA_ALLOCATION_CREATE_MAPPED_BIT;

        vk::Buffer        staging_buffer            = { };
        VmaAllocation     staging_buffer_allocation;
        VmaAllocationInfo staging_buffer_alloc_info = { };
        auto result = vmaCreateBuffer(
            _allocator
          , &buffer_create_info
          , &allocation_create_info
          , reinterpret_cast<VkBuffer*>(&staging_buffer)
          , &staging_buffer_allocation
          , &staging_buffer_alloc_info);

        Ensures(result == VK_SUCCESS);

        std::copy_n(data.data(), data.size(), reinterpret_cast<char*>(staging_buffer_alloc_info.pMappedData));

        vk::Buffer    memory_buffer = { };
        VmaAllocation memory_buffer_allocation;

        buffer_create_info.usage     = static_cast<VkBufferUsageFlags>(usage);
        allocation_create_info.usage = VMA_MEMORY_USAGE_GPU_ONLY;
        allocation_create_info.flags = 0;

        result = vmaCreateBuffer(
            _allocator
          , &buffer_create_info
          , &allocation_create_info
          , reinterpret_cast<VkBuffer*>(&memory_buffer)
          , &memory_buffer_allocation
          , nullptr);

        Ensures(result == VK_SUCCESS);

        /*
        // Copy buffer contents from the staging buffer to the real buffer
        begin_single_time_commands();

        auto buffer_copy_region = vk::BufferCopy()
            .setSrcOffset(0)
            .setDstOffset(0)
            .setSize(buffer_create_info.size);

        _single_time_command_buffer.copyBuffer(staging_buffer, memory_buffer, 1, &buffer_copy_region);

        end_single_time_commands();

        // Destroy the staging buffer
        vmaDestroyBuffer(_allocator, staging_buffer, staging_buffer_allocation);
        */
    }

    buffer::~buffer()
    {
        auto memory_allocation = std::any_cast<VmaAllocation>(_memory_buffer_allocation);
        vmaDestroyBuffer(_allocator, _memory_buffer, memory_allocation);
    }

    const vk::Buffer& buffer::memory_buffer() const noexcept
    {
        return _memory_buffer;
    }

    const std::any& buffer::memory_buffer_allocation() const noexcept
    {
        return _memory_buffer_allocation;
    }

    std::uint32_t buffer::size() const noexcept
    {
        return _size;
    }

    /// Gets the buffer usage.
    buffer_usage buffer::usage() const noexcept
    {
        return _usage;
    }

    /// Gets a subset of data from a buffer object's data store.
    /// \param offset specifies the offset into the buffer object's data store where data replacement will begin, measured in bytes.
    /// \param count specifies the size in bytes of the data store to be obtained.
    std::vector<std::uint8_t> buffer::get_data([[maybe_unused]] std::uint32_t offset, [[maybe_unused]] std::uint32_t count) const noexcept
    {
        return {};
    }

    /// Creates and initializes the buffer object data store.
    /// \param data specifies a span of data that will be copied into the data store for initialization.
    void buffer::set_data([[maybe_unused]] const gsl::span<const std::uint8_t>& data) const noexcept
    {
    }

    /// Creates and initializes the buffer object data store.
    /// \param data specifies a span of data that will be copied into the data store for initialization.
    void buffer::set_data([[maybe_unused]] std::uint32_t offset
                        , [[maybe_unused]] std::uint32_t count
                        , [[maybe_unused]] const gsl::not_null<const void*> data) const noexcept
    {
    }
}
