// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_VULKAN_IMAGE_HPP
#define SCENER_GRAPHICS_VULKAN_IMAGE_HPP

#include <gsl/gsl>
#include <vulkan/vulkan.hpp>

#include "scener/graphics/texture_target.hpp"
#include "scener/graphics/vulkan/vulkan_memory_allocator.hpp"

namespace scener::graphics::vulkan
{
    struct image_storage final
    {
    public:
        image_storage() noexcept;
        image_storage(const vk::Image&             image
                    , const vk::ImageView&         view
                    , const VmaAllocation&         allocation
                    , gsl::not_null<VmaAllocator*> allocator) noexcept;

    public:
        void destroy() noexcept;

    public:
        const vk::Image& image() const noexcept;
        const vk::ImageView& view() const noexcept;
//        const VmaAllocation& image_allocation() const noexcept;

        void set_data(const gsl::span<const std::uint8_t>& data) noexcept;

    private:
        vk::Image     _image;
        vk::ImageView _view;
        VmaAllocation _allocation;
        VmaAllocator* _allocator;
    };
}

#endif
