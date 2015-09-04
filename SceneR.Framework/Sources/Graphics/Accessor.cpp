#include <Graphics/Accessor.hpp>

namespace SceneR
{
    namespace Graphics
    {
        Accessor::Accessor()
            : _attribute_type { AttributeType::Scalar }
            , _component_type { ComponentType::Single }
            , _byte_offset    { 0 }
            , _byte_stride    { 0 }
            , _count          { 0 }
            , _max            { 0 }
            , _min            { 0 }
            , _buffer_view    { nullptr }
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

        const std::size_t& Accessor::byte_offset() const
        {
            return _byte_offset;
        }

        const std::size_t& Accessor::byte_stride() const
        {
            return _byte_stride;
        }

        const std::size_t& Accessor::count() const
        {
            return _count;
        }

        const std::vector<float>& Accessor::max() const
        {
            return _max;
        }

        const std::vector<float>& Accessor::min() const
        {
            return _min;
        }
    }
}
