// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_CONTENT_GLTF_BUFFER_VIEW_HPP
#define SCENER_CONTENT_GLTF_BUFFER_VIEW_HPP

#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include <gsl/span>

namespace scener::content::readers { template <typename T> class content_type_reader; }

namespace scener::content::gltf
{
    class buffer;

    /// GLTF. A view into a buffer.
    class buffer_view final
    {
    public:
        /// Initializes a new instance of the BufferView class.
        buffer_view() = default;

    public:
        /// Gets the offset into the buffer in bytes.
        std::uint32_t byte_offset() const noexcept;

        /// Gets the length of the buffer-view in bytes.
        std::uint32_t byte_length() const noexcept;

        /// Gets the buffer name.
        /// \returns the buffer name.
        const std::string& name() const noexcept;

        /// Gets a view to the buffer data from object's data store.
        /// \returns a view to the buffer data from object's data store.
        gsl::span<const std::uint8_t> get_data() const noexcept;

        /// Gets a view to the buffer data from object's data store.
        /// \param offset specifies the offset into the buffer object's data store where data replacement will begin,
        ///               measured in bytes.
        /// \param count specifies the size in bytes of the data store region being replaced.
        /// \returns a view to the buffer data from object's data store.
        gsl::span<const std::uint8_t> get_data(std::uint32_t offset, std::uint32_t count) const noexcept;

    private:
        std::shared_ptr<buffer> _buffer      { nullptr };
        std::uint32_t           _byte_offset { 0 };
        std::uint32_t           _byte_length { 0 };
        std::string             _name        { };

        template <typename T> friend class scener::content::readers::content_type_reader;
    };
}

#endif // SCENER_CONTENT_GLTF_BUFFER_VIEW_HPP
