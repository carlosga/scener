// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/vulkan/image_storage.hpp"

namespace scener::graphics::vulkan
{
    image_storage::image_storage() noexcept
        : _image            { }
        , _image_view       { }
        , _image_allocation { }
        , _allocator        { nullptr }
    {
    }

    image_storage::image_storage(const vk::Image&     image
                               , const vk::ImageView& view
                               , const VmaAllocation& image_allocation
                               , VmaAllocator*        allocator) noexcept
        : _image            { image }
        , _image_view       { view  }
        , _image_allocation { image_allocation }
        , _allocator        { allocator }
    {
    }

    void image_storage::destroy() noexcept
    {
        vmaDestroyImage(*_allocator, _image, _image_allocation);
    }

    const vk::Image& image_storage::image() const noexcept
    {
        return _image;
    }

    const vk::ImageView& image_storage::image_view() const noexcept
    {
        return _image_view;
    }

    const VmaAllocation& image_storage::image_allocation() const noexcept
    {
        return _image_allocation;
    }
}
