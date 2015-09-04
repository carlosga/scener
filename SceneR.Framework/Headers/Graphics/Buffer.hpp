// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <cstdint>
#include <string>

#include <Graphics/BufferType.hpp>

namespace SceneR
{
    namespace Content
    {
        class BuffersReader;
        class BufferViewsReader;
    }
}

namespace SceneR
{
    namespace Graphics
    {
        class Buffer
        {
        public:
            Buffer() = default;
            ~Buffer() = default;

        public:
            std::string   uri;
            std::uint64_t byteLength;
            BufferType    type;

            friend class SceneR::Content::BuffersReader;
            friend class SceneR::Content::BufferViewsReader;
        };
    }
}

#endif // BUFFER_HPP
