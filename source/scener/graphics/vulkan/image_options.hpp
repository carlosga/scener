// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_VULKAN_IMAGE_OPTIONS_HPP
#define SCENER_GRAPHICS_VULKAN_IMAGE_OPTIONS_HPP

#include <vulkan/vulkan.hpp>

#include <scener/graphics/texture_target.hpp>

namespace scener::graphics::vulkan
{
    struct image_options
    {
        vk::ImageUsageFlags usage;
        texture_target      target;
        vk::Extent3D        extent;
        std::uint32_t       mip_levels;
    };
}

#endif  // SCENER_GRAPHICS_VULKAN_IMAGE_OPTIONS_HPP
