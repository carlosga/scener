#include <Graphics/Accessor.hpp>

#include <Graphics/BufferView.hpp>

namespace SceneR
{
    namespace Graphics
    {
        Accessor::Accessor()
            : _attribute_type  { AttributeType::Scalar }
            , _component_type  { ComponentType::Single }
            , _byte_offset     { 0 }
            , _byte_length     { 0 }
            , _byte_stride     { 0 }
            , _attribute_count { 0 }
            , _max             { 0 }
            , _min             { 0 }
            , _buffer_view     { nullptr }
        {
        }

        Accessor::~Accessor()
        {
        }

        const AttributeType& Accessor::attribute_type() const
        {
            return _attribute_type;
        }

        const ComponentType& Accessor::component_type() const
        {
            return _component_type;
        }

        std::size_t Accessor::byte_offset() const
        {
            return _byte_offset;
        }

        std::size_t Accessor::byte_length() const
        {
            return _byte_length;
        }

        std::size_t Accessor::byte_stride() const
        {
            return _byte_stride;
        }

        std::size_t Accessor::attribute_count() const
        {
            return _attribute_count;
        }

        const std::vector<float>& Accessor::max() const
        {
            return _max;
        }

        const std::vector<float>& Accessor::min() const
        {
            return _min;
        }

        const std::u16string& Accessor::name() const
        {
            return _name;
        }

        std::vector<std::uint8_t> Accessor::get_data() const
        {
            std::vector<std::uint8_t> data(_byte_length, 0);

            _buffer_view->get_data(_byte_offset, _byte_length, data.begin());

            return data;
        }

        void Accessor::get_data(const std::size_t&                  elementOffset
                              , const std::size_t&                  elementCount
                              , std::vector<std::uint8_t>::iterator data) const
        {
            _buffer_view->get_data(_byte_offset + (elementOffset * _byte_stride), elementCount * _byte_stride, data);
        }

        std::size_t Accessor::get_attribute_type_count() const
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

        std::size_t Accessor::get_component_size_in_bytes() const
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
