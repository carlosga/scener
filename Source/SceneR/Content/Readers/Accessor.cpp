// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "Accessor.hpp"

namespace SceneR
{
    namespace Content
    {
        using SceneR::Graphics::ComponentType;

        const AttributeType& Accessor::attribute_type() const noexcept
        {
            return _attribute_type;
        }

        const ComponentType& Accessor::component_type() const noexcept
        {
            return _component_type;
        }

        std::size_t Accessor::byte_offset() const noexcept
        {
            return _byte_offset;
        }

        std::size_t Accessor::byte_length() const noexcept
        {
            return _byte_length;
        }

        std::size_t Accessor::byte_stride() const noexcept
        {
            return ((_byte_stride > 0) ? _byte_stride : get_attribute_type_count() * get_component_size_in_bytes());
        }

        std::size_t Accessor::attribute_count() const noexcept
        {
            return _attribute_count;
        }

        const std::vector<float>& Accessor::max() const noexcept
        {
            return _max;
        }

        const std::vector<float>& Accessor::min() const noexcept
        {
            return _min;
        }

        const std::string& Accessor::name() const noexcept
        {
            return _name;
        }

        const gsl::span<std::uint8_t> Accessor::get_data() const
        {
            return get_data(0, _attribute_count);
        }

        const gsl::span<std::uint8_t> Accessor::get_data(const std::size_t& elementOffset
                                                       , const std::size_t& elementCount) const
        {
            return _buffer_view->get_data(_byte_offset + (elementOffset * byte_stride()), elementCount * byte_stride());
        }

        std::size_t Accessor::get_attribute_type_count() const noexcept
        {
            switch (_attribute_type)
            {
            case AttributeType::Matrix2:
                return 4;

            case AttributeType::Matrix3:
                return 9;

            case AttributeType::Matrix4:
                return 16;

            case AttributeType::Scalar:
                return 1;

            case AttributeType::Vector2:
                return 2;

            case AttributeType::Vector3:
                return 3;

            case AttributeType::Vector4:
                return 4;
            }
        }

        std::size_t Accessor::get_component_size_in_bytes() const noexcept
        {
            switch (_component_type)
            {
            case ComponentType::Byte:
                return sizeof(std::int8_t);

            case ComponentType::Int16:
                return sizeof(std::int16_t);

            case ComponentType::Single:
                return sizeof(float);

            case ComponentType::UByte:
                return sizeof(std::uint8_t);

            case ComponentType::UInt16:
                return sizeof(std::uint16_t);
            }
        }
    }
}
