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
            Accessor() = default;
            ~Accessor() = default;

        public:
            std::shared_ptr<BufferView> bufferView;
            std::uint64_t               byteOffset;
            std::uint8_t                byteStride;
            ComponentType               componentType;
            std::uint64_t               count;
            AttributeType               type;
            std::vector<float>          max;
            std::vector<float>          min;

            friend class SceneR::Content::AccessorsReader;
            friend class SceneR::Content::MeshesReader;
        };
    }
}

#endif // ACCESSOR_HPP
