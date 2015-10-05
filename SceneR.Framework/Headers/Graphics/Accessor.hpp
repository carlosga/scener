// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef GRAPHICS_ACCESSOR_HPP
#define GRAPHICS_ACCESSOR_HPP

#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include <functional>
#include <gsl.h>

#include <Graphics/AttributeType.hpp>
#include <Graphics/BufferView.hpp>
#include <Graphics/ComponentType.hpp>

namespace SceneR
{
    namespace Content
    {
        template <typename T> class ContentTypeReader;
    }

    namespace Graphics
    {
        /**
         * GLTF. A typed accessor into a buffer-view.
         */
        class Accessor final
        {
        public:
            /**
             * Initializes a new instance of the Accessor class.
             */
            Accessor() = default;

            /**
             * Destructor.
             */
            ~Accessor() = default;

        public:
            /**
             * Specifies if the attribute is a scalar, vector, or matrix.
             */
            const AttributeType& attribute_type() const noexcept;

            /**
             * Gets the data type of the components referenced by this accessor.
             */
            const ComponentType& component_type() const noexcept;

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
            const gsl::array_view<std::uint8_t> get_data() const;

            /**
             * Gets the accessor data.
             */
            const gsl::array_view<std::uint8_t> get_data(const std::size_t& elementOffset
                                                       , const std::size_t& elementCount) const;

            std::size_t get_attribute_type_count() const noexcept;

            std::size_t get_component_size_in_bytes() const noexcept;

        private:
            AttributeType               _attribute_type  { AttributeType::Scalar };
            ComponentType               _component_type  { ComponentType::Single };
            std::size_t                 _byte_offset     { 0 };
            std::size_t                 _byte_length     { 0 };
            std::size_t                 _byte_stride     { 0 };
            std::size_t                 _attribute_count { 0 };
            std::vector<float>          _max             { 0 };
            std::vector<float>          _min             { 0 };
            std::shared_ptr<BufferView> _buffer_view     { nullptr };
            std::string                 _name            { };

            template <typename T> friend class SceneR::Content::ContentTypeReader;
        };
    }
}

#endif // GRAPHICS_ACCESSOR_HPP
