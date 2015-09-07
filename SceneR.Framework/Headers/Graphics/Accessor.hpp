// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef ACCESSOR_HPP
#define ACCESSOR_HPP

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include <Graphics/AttributeType.hpp>
#include <Graphics/ComponentType.hpp>

namespace  SceneR
{
    namespace Content
    {
        class AccessorsReader;
        class MeshesReader;
    }
}

namespace SceneR
{
    namespace Graphics
    {
        class BufferView;

        class Accessor
        {
        public:
            Accessor();
            ~Accessor();

        public:
            const AttributeType& attribute_type() const;

            const ComponentType& component_type() const;

            std::size_t byte_offset() const;

            std::size_t byte_length() const;

            std::size_t byte_stride() const;

            std::size_t attribute_count() const;

            const std::vector<float>& max() const;

            const std::vector<float>& min() const;

            const std::u16string& name() const;

            std::vector<std::uint8_t> get_data() const;

            void get_data(const std::size_t&                  elementOffset
                        , const std::size_t&                  elementCount
                        , std::vector<std::uint8_t>::iterator data) const;

            std::size_t get_attribute_type_count() const;

            std::size_t get_component_size_in_bytes() const;

        private:
            AttributeType               _attribute_type;
            ComponentType               _component_type;
            std::size_t                 _byte_offset;
            std::size_t                 _byte_length;
            std::size_t                 _byte_stride;
            std::size_t                 _attribute_count;
            std::vector<float>          _max;
            std::vector<float>          _min;
            std::shared_ptr<BufferView> _buffer_view;
            std::u16string              _name;

            friend class SceneR::Content::AccessorsReader;
        };
    }
}

#endif // ACCESSOR_HPP
