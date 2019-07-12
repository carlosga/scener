// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_VULKAN_TEXTURE_OBJECT_HPP
#define SCENER_GRAPHICS_VULKAN_TEXTURE_OBJECT_HPP

#include <cstdint>

#include <gsl/gsl>
#include <vulkan/vulkan.hpp>

#include "scener/graphics/texture_target.hpp"
#include "scener/graphics/vulkan/vulkan_memory_allocator.hpp"

namespace scener::graphics::vulkan
{
    struct texture_object final
    {
    public:
        texture_object() noexcept;

    public:
        void destroy() noexcept;
        void set_data(const gsl::span<const std::uint8_t>& data) noexcept;

    public:
        std::uint32_t      width;
        std::uint32_t      height;
        vk::Sampler        sampler;
        vk::Image          image;
        vk::ImageView      view;
        vk::ImageLayout    image_layout;
        VmaAllocation      allocation;
        VmaAllocationInfo  allocation_info;
        VmaAllocator*      allocator;
    };
}

#endif
