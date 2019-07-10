// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/vulkan/image_storage.hpp"

namespace scener::graphics::vulkan
{
    image_storage::image_storage() noexcept
        : _image      { }
        , _view       { }
        , _allocation { }
        , _allocator  { nullptr }
    {
    }

    image_storage::image_storage(const vk::Image&             image
                               , const vk::ImageView&         view
                               , const VmaAllocation&         allocation
                               , gsl::not_null<VmaAllocator*> allocator) noexcept
        : _image      { image }
        , _view       { view  }
        , _allocation { allocation }
        , _allocator  { allocator }
    {
    }

    void image_storage::destroy() noexcept
    {
        vmaDestroyImage(*_allocator, _image, _allocation);
    }

    const vk::Image& image_storage::image() const noexcept
    {
        return _image;
    }

    const vk::ImageView& image_storage::view() const noexcept
    {
        return _view;
    }

//    const VmaAllocation& image_storage::allocation() const noexcept
//    {
//        return _allocation;
//    }

    void image_storage::set_data(const gsl::span<const std::uint8_t>& data) noexcept
    {
        void* mappedData;
        vmaMapMemory(*_allocator, _allocation, &mappedData);
        memcpy(mappedData, data.data(), data.size());
        vmaUnmapMemory(*_allocator, _allocation);
    }
}
