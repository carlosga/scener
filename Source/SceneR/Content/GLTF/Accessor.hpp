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

namespace SceneR { namespace Content { namespace Readers {

template <typename T> class ContentTypeReader;

}}}

namespace SceneR { namespace Content { namespace GLTF {

class BufferView;

/**
 * GLTF. A typed accessor into a buffer-view.
 */
class Accessor final
{
public:
    /**
     * Initializes a new instance of the Accessor class.
     */
    Accessor() noexcept = default;

    /**
     * Destructor.
     */
    ~Accessor() = default;

public:
    /**
     * Specifies if the attribute is a scalar, vector, or matrix.
     */
    AttributeType attribute_type() const noexcept;

    /**
     * Gets the data type of the components referenced by this accessor.
     */
    SceneR::Graphics::ComponentType component_type() const noexcept;

    /**
     * Gets the offset relative to the buffer-view in bytes.
     */
    std::size_t byte_offset() const noexcept;

    /**
     * Gets the size, in bytes, of the data referenced by this accessor.
     */
    std::size_t byte_length() const noexcept;

    /**
     * Gets the stride, in bytes, between attributes referenced by this accessor.
     */
    std::size_t byte_stride() const noexcept;

    /**
     * Gets the number of attributes referenced by this accessor,
     * not to be confused with the number of bytes or number of components.
     */
    std::size_t attribute_count() const noexcept;

    /**
     * Gets the maximum value of each component in this attribute.
     */
    const std::vector<float>& max() const noexcept;

    /**
     * Gets the minimum value of each component in this attribute.
     */
    const std::vector<float>& min() const noexcept;

    /**
     * Gets the accessor name.
     */
    const std::string& name() const noexcept;

    /**
     * Gets the accessor data.
     */
    gsl::span<std::uint8_t> get_data() const;

    /**
     * Gets the accessor data.
     */
    gsl::span<std::uint8_t> get_data(std::size_t elementOffset, std::size_t elementCount) const;

    /**
     * Gets the element at the given offset from the accessor buffer.
     */
    template <typename T>
    T get_element(std::size_t elementOffset) const noexcept
    {
        T    result;
        auto buffer = get_data(elementOffset, 1);

        std::copy_n(buffer.begin(), sizeof(T), reinterpret_cast<char*>(&result));

        return result;
    }

private:
    std::size_t get_attribute_type_count() const noexcept;
    std::size_t get_component_size_in_bytes() const noexcept;

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
