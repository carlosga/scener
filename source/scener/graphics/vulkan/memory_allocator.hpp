// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
// ==================================================================================================

#ifndef SCENER_GRAPHICS_VULKAN_ALLOCATOR_HPP
#define SCENER_GRAPHICS_VULKAN_ALLOCATOR_HPP

#include <vulkan/vulkan.hpp>

struct VmaAllocator_T;

namespace scener::graphics::vulkan
{
     class memory_allocator final
    {
    public:
        memory_allocator(const vk::PhysicalDevice& physical_device, const vk::Device& logical_device) noexcept;
        ~memory_allocator() noexcept;

    public:
        VmaAllocator_T* allocator() const noexcept;

    private:
        VmaAllocator_T* _allocator;
    };
}

#endif
