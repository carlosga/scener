// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef GRAPHICS_ACCESSOR_HPP
#define GRAPHICS_ACCESSOR_HPP

#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include <Graphics/AttributeType.hpp>
#include <Graphics/ComponentType.hpp>

namespace SceneR
{
    namespace Content
    {
        template <typename T> class ContentTypeReader;
    }

    namespace Graphics
    {
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
            Accessor();

            /**
             * Destructor.
             */
            ~Accessor();

        public:
            /**
             * Specifies if the attribute is a scalar, vector, or matrix.
             */
            const AttributeType& attribute_type() const;

            /**
             * Gets the data type of the components referenced by this accessor.
             */
            const ComponentType& component_type() const;

            /**
             * Gets the offset relative to the buffer-view in bytes.
             */
            std::size_t byte_offset() const;

            /**
             * Gets the size, in bytes, of the data referenced by this accessor.
             */
            std::size_t byte_length() const;

            /**
             * Gets the stride, in bytes, between attributes referenced by this accessor.
             */
            std::size_t byte_stride() const;

            /**
             * Gets the number of attributes referenced by this accessor,
             * not to be confused with the number of bytes or number of components.
             */
            std::size_t attribute_count() const;

            /**
             * Gets the maximum value of each component in this attribute.
             */
            const std::vector<float>& max() const;

            /**
             * Gets the minimum value of each component in this attribute.
             */
            const std::vector<float>& min() const;

            /**
             * Gets the accessor name.
             */
            const std::u16string& name() const;

            /**
             * Gets the accessor data.
             */
            std::vector<std::uint8_t> get_data() const;

            /**
             * Gets the accessor data.
             */
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

            template <typename T> friend class SceneR::Content::ContentTypeReader;
        };
    }
}

#endif // GRAPHICS_ACCESSOR_HPP
