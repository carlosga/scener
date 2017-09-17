// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
// ==================================================================================================

#include "scener/graphics/vulkan/memory_allocator.hpp"

#include <gsl/gsl_assert>

#define VMA_IMPLEMENTATION
#include <vk_mem_alloc.h>

namespace scener::graphics::vulkan
{
    memory_allocator::memory_allocator(const vk::PhysicalDevice& physical_device, const vk::Device& logical_device) noexcept
        : _allocator { nullptr }
    {
        VmaAllocatorCreateInfo allocatorInfo = { };
        allocatorInfo.physicalDevice = physical_device;
        allocatorInfo.device         = logical_device;

        auto result = vmaCreateAllocator(&allocatorInfo, &_allocator);

        Ensures(result == VK_SUCCESS);
    }

    memory_allocator::~memory_allocator() noexcept
    {
        vmaDestroyAllocator(_allocator);
    }

    VmaAllocator_T* memory_allocator::allocator() const noexcept
    {
        return _allocator;
    }

    vk::Image memory_allocator::allocate_image(const vk::ImageCreateInfo& image_create_info) const noexcept
    {
        VmaAllocationCreateInfo allocation_create_info = {
            VMA_ALLOCATION_CREATE_OWN_MEMORY_BIT
          , VMA_MEMORY_USAGE_CPU_ONLY
          , 0
          , 0
          , nullptr
          , nullptr
        };

        vk::Image     image;
        VmaAllocation allocation;

        auto result = vmaCreateImage(
            _allocator
          , reinterpret_cast<const VkImageCreateInfo*>(&image_create_info)
          , &allocation_create_info
          , reinterpret_cast<VkImage*>(&image)
          , &allocation
          , nullptr);

        Ensures(result == VK_SUCCESS);

        return image;
    }
}
