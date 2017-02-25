// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_CONTENT_GLTF_BUFFER_HPP
#define SCENER_CONTENT_GLTF_BUFFER_HPP

#include <cstdint>
#include <cstddef>
#include <string>
#include <vector>

#include <gsl/span>

namespace scener::content::readers { template <typename T> class content_type_reader; }

namespace scener::content::gltf
{
    /// GLTF. Buffers contain geometry, animation, or skins.
    class buffer final
    {
    public:
        /// Initializes a new instance of the Buffer class.
        buffer() = default;

    public:
        /// Gets the buffer name.
        /// \returns the buffer name.
        const std::string& name() const noexcept;

        /// Gets the buffer uri.
        /// \returns the buffer uri.
        const std::string& uri() const noexcept;

        /// Gets the length in bytes of the buffer data.
        /// \returns the length in bytes of the buffer data.
        std::size_t byte_length() const noexcept;

        /// Gets a view to the buffer data.
        /// \param offset specifies the offset into the buffer object's data store where data replacement will begin,
        ///               measured in bytes.
        /// \param count specifies the size in bytes of the data store region being replaced.
        /// \returns a view to the buffer data.
        gsl::span<const std::uint8_t> get_data(std::size_t offset, std::size_t count) const noexcept;

        /// Sets the buffer data.
        /// \param buffer the buffer data.
        void set_data(const std::vector<std::uint8_t>& buffer) noexcept;

    private:
        std::size_t               _byte_length { 0 };
        std::vector<std::uint8_t> _data        { };
        std::string               _name        { };
        std::string               _uri         { };

        template <typename T> friend class scener::content::readers::content_type_reader;
    };
}

#endif // SCENER_CONTENT_GLTF_BUFFER_HPP
