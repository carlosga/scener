// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_CONTENT_GLTF_ACCESSOR_HPP
#define SCENER_CONTENT_GLTF_ACCESSOR_HPP

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <vector>

#include <gsl.h>

#include "SceneR/Content/GLTF/AttributeType.hpp"
#include "SceneR/Graphics/ComponentType.hpp"

namespace SceneR { namespace Content { namespace Readers { template <typename T> class ContentTypeReader; } } }

namespace SceneR { namespace Content { namespace GLTF {

class BufferView;

/// GLTF. A typed accessor into a buffer-view.
class Accessor final
{
public:
    /// Initializes a new instance of the Accessor class.
    Accessor() noexcept = default;

public:
    /// Specifies if the attribute is a scalar, vector, or matrix.
    /// \returns the attribute type.
    AttributeType attribute_type() const noexcept;

    /// Gets the data type of the components referenced by this accessor.
    /// \returns the data type of the components referenced by this accessor.
    SceneR::Graphics::ComponentType component_type() const noexcept;

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
    /// \param elementOffset the offset of the element to return.
    /// \returns the requested element.
    template <typename T, typename = std::enable_if_t<std::is_constructible<T>::value>>
    inline T get_element(std::size_t elementOffset) const noexcept
    {
        T    result;
        auto buffer = get_data(elementOffset, 1);

        Ensures(sizeof(T) == buffer.size());

        std::copy_n(buffer.begin(), sizeof(T), reinterpret_cast<char*>(&result));

        return result;
    }

private:
    constexpr std::size_t get_attribute_type_count() const noexcept
    {
        switch (_attribute_type)
        {
        case AttributeType::matrix2:
            return 4;

        case AttributeType::matrix3:
            return 9;

        case AttributeType::matrix4:
            return 16;

        case AttributeType::scalar:
            return 1;

        case AttributeType::vector2:
            return 2;

        case AttributeType::vector3:
            return 3;

        case AttributeType::vector4:
            return 4;
        }
    }

    constexpr std::size_t get_component_size_in_bytes() const noexcept
    {
        switch (_component_type)
        {
        case SceneR::Graphics::ComponentType::byte:
            return sizeof(std::int8_t);

        case SceneR::Graphics::ComponentType::int16:
            return sizeof(std::int16_t);

        case SceneR::Graphics::ComponentType::single:
            return sizeof(float);

        case SceneR::Graphics::ComponentType::ubyte:
            return sizeof(std::uint8_t);

        case SceneR::Graphics::ComponentType::uint16:
            return sizeof(std::uint16_t);
        }
    }

private:
    AttributeType               _attribute_type  { AttributeType::scalar };
    std::size_t                 _attribute_count { 0 };
    std::shared_ptr<BufferView> _buffer_view     { nullptr };
    std::size_t                 _byte_offset     { 0 };
    std::size_t                 _byte_length     { 0 };
    std::size_t                 _byte_stride     { 0 };
    Graphics::ComponentType     _component_type  { Graphics::ComponentType::single };
    std::vector<float>          _max             { 0 };
    std::vector<float>          _min             { 0 };
    std::string                 _name            { };

    template <typename T> friend class SceneR::Content::Readers::ContentTypeReader;
};

}}}

#endif // SCENER_CONTENT_GLTF_ACCESSOR_HPP
