// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
// ==================================================================================================

#include "scener/graphics/vulkan/memory_allocator.hpp"

#define VMA_IMPLEMENTATION
#include <vk_mem_alloc.h>

namespace scener::graphics::vulkan
{
    memory_allocator::memory_allocator(const vk::PhysicalDevice& physical_device, const vk::Device& logical_device) noexcept
    {
        VmaAllocatorCreateInfo allocatorInfo = { };
        allocatorInfo.physicalDevice = (VkPhysicalDevice)physical_device;
        allocatorInfo.device         = (VkDevice)logical_device;

        vmaCreateAllocator(&allocatorInfo, &_allocator);
    }

    memory_allocator::~memory_allocator() noexcept
    {
        vmaDestroyAllocator(_allocator);
    }

    VmaAllocator_T* memory_allocator::allocator() const noexcept
    {
        return _allocator;
    }
}
