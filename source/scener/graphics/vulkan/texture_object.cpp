// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/vulkan/texture_object.hpp"

namespace scener::graphics::vulkan
{
    texture_object::texture_object() noexcept
        : width           { 0 }
        , height          { 0 }
        , sampler         { }
        , image           { }
        , view            { }
        , image_layout    { vk::ImageLayout::eUndefined }
        , allocation      { }
        , allocation_info { }
        , allocator       { }
    {
    }

    void texture_object::destroy() noexcept
    {
        vmaDestroyImage(*allocator, image, allocation);
    }

    void texture_object::set_data(const gsl::span<const std::uint8_t>& data) noexcept
    {
        void* mappedData;
        vmaMapMemory(*allocator, allocation, &mappedData);
        memcpy(mappedData, data.data(), data.size());
        vmaUnmapMemory(*allocator, allocation);
    }
}
