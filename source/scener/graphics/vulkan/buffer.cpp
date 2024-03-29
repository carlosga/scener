// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
// ==================================================================================================

#include "scener/graphics/vulkan/buffer.hpp"

#include <any>
#include <algorithm>

namespace scener::graphics::vulkan
{
    buffer::buffer(buffer_usage usage, vk::SharingMode sharing_mode, std::uint64_t count, VmaAllocator* allocator) noexcept
        : _usage     { usage }
        , _size      { count }
        , _buffers   { }
        , _allocator { allocator }
    {
        std::uint32_t buffer_count = 1;

        VkBufferCreateInfo buffer_create_info = { };

        buffer_create_info.sType       = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        buffer_create_info.usage       = static_cast<VkBufferUsageFlags>(usage);
        buffer_create_info.sharingMode = static_cast<VkSharingMode>(sharing_mode);
        buffer_create_info.size        = count;

        VmaAllocationCreateInfo allocation_create_info = { };

        if ((usage & buffer_usage::index_buffer) == buffer_usage::index_buffer)
        {
            allocation_create_info.usage         = VMA_MEMORY_USAGE_GPU_ONLY;
            allocation_create_info.requiredFlags = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
        }
        else if ((usage & buffer_usage::vertex_buffer) == buffer_usage::vertex_buffer)
        {
            allocation_create_info.usage         = VMA_MEMORY_USAGE_GPU_ONLY;
            allocation_create_info.requiredFlags = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
        }
        else if ((usage & buffer_usage::uniform_buffer) == buffer_usage::uniform_buffer)
        {
            allocation_create_info.usage = VMA_MEMORY_USAGE_CPU_ONLY;
            allocation_create_info.flags = VMA_ALLOCATION_CREATE_MAPPED_BIT;
        }

        _buffers.resize(buffer_count);

        for (std::uint32_t i = 0; i < buffer_count; ++i)
        {
            auto result = vmaCreateBuffer(
                *_allocator
              , &buffer_create_info
              , &allocation_create_info
              , reinterpret_cast<VkBuffer*>(&_buffers[i].memory_buffer)
              , &_buffers[i].memory_buffer_allocation
              , &_buffers[i].memory_buffer_allocation_info);

            Ensures(result == VK_SUCCESS);
        }
    }

    buffer::~buffer()
    {
        for (std::uint32_t i = 0; i < _buffers.size(); ++i)
        {
            vmaDestroyBuffer(*_allocator, _buffers[i].memory_buffer, _buffers[i].memory_buffer_allocation);
        }

        _buffers.clear();
    }

    const buffer_resources& buffer::resources(std::uint32_t index) const noexcept
    {
        Ensures(index < _buffers.size());
        return _buffers[index];
    }

    std::uint64_t buffer::size() const noexcept
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
    std::vector<std::uint8_t> buffer::get_data([[maybe_unused]] std::uint64_t offset, [[maybe_unused]] std::uint64_t count) const noexcept
    {
        return {};
    }

    /// Sets the buffer data.
    /// \param data specifies a span of data that will be copied into the data store for initialization.
    void buffer::set_data([[maybe_unused]] std::uint64_t offset
                        , [[maybe_unused]] std::uint64_t count
                        , [[maybe_unused]] gsl::not_null<const void*> data) const noexcept
    {
        Ensures(offset <= _size);
        Ensures(count <= _size);
        Ensures(offset + count <= _size);

        for (std::uint32_t i = 0; i < _buffers.size(); ++i)
        {
             auto mapped_data = reinterpret_cast<char*>(_buffers[i].memory_buffer_allocation_info.pMappedData) + offset;

             // Buffer is already mapped (VMA_ALLOCATION_CREATE_MAPPED_BIT)
             memcpy(mapped_data, data, count);
        }
    }
}
