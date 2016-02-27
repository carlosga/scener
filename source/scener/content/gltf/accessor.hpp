// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_CONTENT_GLTF_ACCESSOR_HPP
#define SCENER_CONTENT_GLTF_ACCESSOR_HPP

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <vector>

#include <gsl.h>

#include "scener/content/gltf/attribute_type.hpp"
#include "scener/graphics/component_type.hpp"

namespace scener { namespace content { namespace readers { template <typename T> class content_type_reader; } } }

namespace scener { namespace content { namespace gltf {

class buffer_view;

/// GLTF. A typed accessor into a buffer-view.
class accessor final
{
public:
    /// Initializes a new instance of the Accessor class.
    accessor() noexcept = default;

public:
    /// Specifies if the attribute is a scalar, vector, or matrix.
    /// \returns the attribute type.
    gltf::attribute_type attribute_type() const noexcept;

    /// Gets the data type of the components referenced by this accessor.
    /// \returns the data type of the components referenced by this accessor.
    graphics::component_type component_type() const noexcept;

    /// Gets the offset relative to the buffer-view in bytes.
    /// \returns the offset relative to the buffer-view in bytes.
    std::size_t byte_offset() const noexcept;

    /// Gets the size, in bytes, of the data referenced by this accessor.
    /// \returns the size, in bytes, of the data referenced by this accessor.
    std::size_t byte_length() const noexcept;

    /// Gets the stride, in bytes, between attributes referenced by this accessor.
    /// \returns the stride, in bytes, between attributes referenced by this accessor.
    std::size_t byte_stride() const noexcept;

    /// Gets the number of attributes referenced by this accessor, not to be confused with the number of bytes or
    /// number of components.
    /// \returns the number of attributes referenced by this accessor.
    std::size_t attribute_count() const noexcept;

    /// Gets the maximum value of each component in this attribute.
    /// \returns the maximum value of each component in this attribute.
    const std::vector<float>& max() const noexcept;

    /// Gets the minimum value of each component in this attribute.
    /// \returns the minimum value of each component in this attribute.
    const std::vector<float>& min() const noexcept;

    /// Gets the accessor name.
    /// \returns the name of the accessor
    const std::string& name() const noexcept;

    /// Gets a view to the accessor data.
    /// \returns a view to the accessor data.
    gsl::span<const std::uint8_t> get_data() const noexcept;

    /// Gets a view to the accessor data.
    /// \param offset specifies the element offset.
    /// \param count specifies the size in bytes of the data store region being replaced.
    gsl::span<const std::uint8_t> get_data(std::size_t offset, std::size_t count) const noexcept;

    /// Gets the element at the given offset from the accessor buffer.
    /// \param offset the offset of the element to return.
    /// \returns the requested element.
    template <typename T, typename = std::enable_if_t<std::is_constructible<T>::value>>
    inline T get_element(std::size_t offset) const noexcept
    {
        T    result;
        auto buffer = get_data(offset, 1);

        Ensures(sizeof(T) == buffer.size());

        std::copy_n(buffer.begin(), sizeof(T), reinterpret_cast<char*>(&result));

        return result;
    }

private:
    constexpr std::size_t get_attribute_type_count() const noexcept
    {
        switch (_attribute_type)
        {
        case attribute_type::matrix2:
            return 4;

        case attribute_type::matrix3:
            return 9;

        case attribute_type::matrix4:
            return 16;

        case attribute_type::scalar:
            return 1;

        case attribute_type::vector2:
            return 2;

        case attribute_type::vector3:
            return 3;

        case attribute_type::vector4:
            return 4;
        }
    }

    constexpr std::size_t get_component_size_in_bytes() const noexcept
    {
        switch (_component_type)
        {
        case scener::graphics::component_type::byte:
            return sizeof(std::int8_t);

        case scener::graphics::component_type::int16:
            return sizeof(std::int16_t);

        case scener::graphics::component_type::single:
            return sizeof(float);

        case scener::graphics::component_type::ubyte:
            return sizeof(std::uint8_t);

        case scener::graphics::component_type::uint16:
            return sizeof(std::uint16_t);
        }
    }

private:
    gltf::attribute_type         _attribute_type  { gltf::attribute_type::scalar };
    std::size_t                  _attribute_count { 0 };
    std::shared_ptr<buffer_view> _buffer_view     { nullptr };
    std::size_t                  _byte_offset     { 0 };
    std::size_t                  _byte_length     { 0 };
    std::size_t                  _byte_stride     { 0 };
    graphics::component_type     _component_type  { graphics::component_type::single };
    std::vector<float>           _max             { 0 };
    std::vector<float>           _min             { 0 };
    std::string                  _name            { };

    template <typename T> friend class scener::content::readers::content_type_reader;
};

}}}

#endif // SCENER_CONTENT_GLTF_ACCESSOR_HPP
