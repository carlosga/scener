// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_VULKAN_IMAGE_HPP
#define SCENER_GRAPHICS_VULKAN_IMAGE_HPP

#include <any>
#include <functional>

#include <vulkan/vulkan.hpp>

#include <scener/graphics/texture_target.hpp>

namespace scener::graphics::vulkan
{
    struct image_storage final
    {
    public:
        image_storage(const vk::Image& image, const vk::ImageView& view, const std::any& image_allocation)
            : _image            { image }
            , _image_view       { view  }
            , _image_allocation { image_allocation }
        {
        }

    public:
        const vk::Image& image() const noexcept
        {
            return _image;
        }

        const vk::ImageView& image_view() const noexcept
        {
            return _image_view;
        }

        const std::any& image_allocation() const noexcept
        {
            return _image_allocation;
        }

    private:
        vk::Image     _image;
        vk::ImageView _image_view;
        std::any      _image_allocation;
    };
}

#endif
