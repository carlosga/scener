// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef BUFFERUSAGE_HPP
#define BUFFERUSAGE_HPP

#include <System/Graphics/Platform.hpp>
#include <System/Core.hpp>

namespace SceneR
{
    namespace Graphics
    {
        enum class BufferUsage : System::UInt32
        {
            StreamDraw  = GL_STREAM_DRAW,
            StreamRead  = GL_STREAM_READ,
            StreamCopy  = GL_STREAM_COPY,
            StaticDraw  = GL_STATIC_DRAW,
            StaticRead  = GL_STATIC_READ,
            StaticCopy  = GL_STATIC_COPY,
            DynamicDraw = GL_DYNAMIC_DRAW,
            DynamicRead = GL_DYNAMIC_READ,
            DynamicCopy = GL_DYNAMIC_COPY
        };
    }
}

#endif // BUFFERUSAGE_HPP
