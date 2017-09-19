// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/vulkan/image.hpp"

#include <utility>

#include <vulkan/vulkan.hpp>

namespace scener::graphics::vulkan
{
    image::image(vk::Image&& image, vk::ImageView&& view)
        : _image      { std::forward<vk::Image>(image) }
        , _image_view { std::forward<vk::ImageView>(view)  }
    {
    }
}

