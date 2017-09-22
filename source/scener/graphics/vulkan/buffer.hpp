// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_OPENGL_BUFFER_HPP
#define SCENER_GRAPHICS_OPENGL_BUFFER_HPP

#include <cstddef>
#include <cstdint>
#include <vector>

#include <gsl/gsl>

#include "scener/graphics/vulkan/buffer_target.hpp"

namespace scener::graphics::vulkan
{
    /// Represents an OpenGL buffer object.
    class buffer final
    {
    public:
        /// Initializes a new instance of the Buffer class.
        /// \param target the buffer target.
        buffer(buffer_target target) noexcept;

    public:
        /// Gets the buffer object identifier.
        std::uint32_t id() const noexcept;

        /// Gets the buffer object target.
        buffer_target target() const noexcept;

        /// Gets a subset of data from a buffer object's data store.
        /// \param offset specifies the offset into the buffer object's data store where data replacement will begin, measured in bytes.
        /// \param count specifies the size in bytes of the data store to be obtained.
        std::vector<std::uint8_t> get_data(std::size_t offset, std::size_t count) const noexcept;

        /// Creates and initializes the buffer object data store.
        /// \param size specifies the size in bytes of the buffer object's new data store.
        /// \param data specifies a pointer to data that will be copied into the data store for initialization.
        void set_data(std::size_t size, gsl::not_null<const void*> data) const noexcept;

        /// Updates a subset of a buffer object's data store.
        /// \param offset specifies the offset into the buffer object's data store where data replacement will begin, measured in bytes.
        /// \param count specifies the size in bytes of the data store region being replaced.
        /// \param data specifies a pointer to the new data that will be copied into the data store.
        void set_data(std::size_t offset, std::size_t count, gsl::not_null<const void*> data) const noexcept;

        /// Invalidates the content of a buffer object's data store
        void invalidate() const noexcept;

        /// Invalidates a region of a buffer object's data store
        /// \param offset the offset within the buffer's data store of the start of the range to be invalidated.
        /// \param count the length of the range within the buffer's data store to be invalidated.
        void invalidate(std::size_t offset, std::size_t count) const noexcept;

    private:
        std::uint32_t _id;
        buffer_target _target;
    };
}

#endif // SCENER_GRAPHICS_OPENGL_BUFFER_HPP
