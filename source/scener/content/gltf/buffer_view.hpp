// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_CONTENT_GLTF_BUFFERVIEW_HPP
#define SCENER_CONTENT_GLTF_BUFFERVIEW_HPP

#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include <gsl.h>

namespace scener { namespace content { namespace readers { template <typename T> class ContentTypeReader; } } }

namespace scener { namespace content { namespace gltf {

class buffer;

/// GLTF. A view into a buffer.
class buffer_view final
{
public:
    /// Initializes a new instance of the BufferView class.
    buffer_view() = default;

public:
    /// Gets the offset into the buffer in bytes.
    std::size_t byte_offset() const noexcept;

    /// Gets the length of the buffer-view in bytes.
    std::size_t byte_length() const noexcept;

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
    gsl::span<const std::uint8_t> get_data(std::size_t offset, std::size_t count) const noexcept;

private:
    std::shared_ptr<buffer> _buffer      { nullptr };
    std::size_t             _byte_offset { 0 };
    std::size_t             _byte_length { 0 };
    std::string             _name        { };

    template <typename T> friend class scener::content::readers::ContentTypeReader;
};

}}}

#endif // SCENER_CONTENT_GLTF_BUFFERVIEW_HPP
