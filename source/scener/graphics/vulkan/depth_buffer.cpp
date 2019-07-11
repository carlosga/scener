// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/vulkan/depth_buffer.hpp"

namespace scener::graphics::vulkan
{
    depth_buffer::depth_buffer() noexcept
        : _image      { }
        , _view       { }
        , _allocation { }
        , _allocator  { nullptr }
    {
    }

    depth_buffer::depth_buffer(const vk::Image&             image
                             , const vk::ImageView&         view
                             , const VmaAllocation&         allocation
                             , gsl::not_null<VmaAllocator*> allocator) noexcept
        : _image      { image }
        , _view       { view  }
        , _allocation { allocation }
        , _allocator  { allocator }
    {
    }

    void depth_buffer::destroy() noexcept
    {
        vmaDestroyImage(*_allocator, _image, _allocation);        
    }

    const vk::Image& depth_buffer::image() const noexcept
    {
        return _image;
    }

    const vk::ImageView& depth_buffer::view() const noexcept
    {
        return _view;
    }
}
