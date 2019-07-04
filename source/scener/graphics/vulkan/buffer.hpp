// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_OPENGL_BUFFER_HPP
#define SCENER_GRAPHICS_OPENGL_BUFFER_HPP

#include <any>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <memory>
#include <vector>

#include <gsl/gsl>
#include <vulkan/vulkan.hpp>

#include "scener/graphics/vulkan/buffer_usage.hpp"

struct VmaAllocator_T;
struct VmaAllocation_T;

namespace scener::graphics::vulkan
{
    /// Represents a Vulkan buffer object.
    class buffer final
    {
    public:
        /// Initializes a new instance of the Buffer class.
        /// \param usage the buffer usage.
        /// \param size the buffer size.
        /// \param buffer the vulkan buffer.
        buffer(buffer_usage usage, vk::SharingMode sharing_mode, std::uint64_t count, VmaAllocator_T* allocator) noexcept;

        ~buffer();

    public:
        std::uint64_t size() const noexcept;

        /// Gets the buffer usage.
        buffer_usage usage() const noexcept;

        const vk::Buffer& memory_buffer() const noexcept;

        /// Gets a subset of data from a buffer object's data store.
        /// \param offset specifies the offset into the buffer object's data store where data replacement will begin, measured in bytes.
        /// \param count specifies the size in bytes of the data store to be obtained.
        std::vector<std::uint8_t> get_data([[maybe_unused]] std::uint64_t offset, [[maybe_unused]] std::uint64_t count) const noexcept;

        /// Creates and initializes the buffer object data store.
        /// \param data specifies a span of data that will be copied into the data store for initialization.
        void set_data([[maybe_unused]] std::uint64_t offset
                    , [[maybe_unused]] std::uint64_t count
                    , [[maybe_unused]] const gsl::not_null<const void*> data) const noexcept;

        void transfer_data(const gsl::span<const std::uint8_t>& data, const vk::CommandBuffer& command_buffer) noexcept;

    private:
        buffer_usage     _usage;
        vk::SharingMode  _sharing_mode;
        std::uint64_t    _size;
        vk::Buffer       _memory_buffer;
        VmaAllocation_T* _memory_buffer_allocation;
        VmaAllocator_T*  _allocator;
    };
}

#endif // SCENER_GRAPHICS_OPENGL_BUFFER_HPP
