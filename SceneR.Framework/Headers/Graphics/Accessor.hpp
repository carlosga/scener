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

            const std::size_t& byte_offset() const;

            const std::size_t& byte_stride() const;

            const std::size_t& count() const;

            const std::vector<float>& max() const;

            const std::vector<float>& min() const;

        private:
            AttributeType               _attribute_type;
            ComponentType               _component_type;
            std::size_t                 _byte_offset;
            std::size_t                 _byte_stride;
            std::size_t                 _count;
            std::vector<float>          _max;
            std::vector<float>          _min;
            std::shared_ptr<BufferView> _buffer_view;

            friend class SceneR::Content::AccessorsReader;
            friend class SceneR::Content::MeshesReader;
        };
    }
}

#endif // ACCESSOR_HPP