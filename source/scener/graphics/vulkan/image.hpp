// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_VULKAN_IMAGE_HPP
#define SCENER_GRAPHICS_VULKAN_IMAGE_HPP

#include <vulkan/vulkan.hpp>

#include <scener/graphics/texture_target.hpp>

namespace scener::graphics::vulkan
{
    class image final
    {
    public:
        image(vk::Image&& image, vk::ImageView&& view);

    private:
        vk::Image     _image;
        vk::ImageView _image_view;
    };
}

#endif
