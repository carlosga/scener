// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_OPENGL_BUFFERUSAGE_HPP
#define SCENER_GRAPHICS_OPENGL_BUFFERUSAGE_HPP

#include <cstdint>

#include "SceneR/Graphics/OpenGL/glad.hpp"

namespace SceneR { namespace Graphics { namespace OpenGL {

/**
 * OpenGL Buffer usages.
 */
enum class BufferUsage : std::uint32_t
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

}}}

#endif // SCENER_GRAPHICS_OPENGL_BUFFERUSAGE_HPP
