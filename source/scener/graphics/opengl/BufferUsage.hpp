// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_OPENGL_BUFFERUSAGE_HPP
#define SCENER_GRAPHICS_OPENGL_BUFFERUSAGE_HPP

#include <cstdint>

#include "SceneR/Graphics/OpenGL/glad.hpp"

namespace scener { namespace graphics { namespace opengl {

/// OpenGL Buffer usages.
enum class BufferUsage : std::uint32_t
{
    stream_draw  = GL_STREAM_DRAW
  , stream_read  = GL_STREAM_READ
  , stream_copy  = GL_STREAM_COPY
  , static_draw  = GL_STATIC_DRAW
  , static_read  = GL_STATIC_READ
  , static_copy  = GL_STATIC_COPY
  , dynamic_draw = GL_DYNAMIC_DRAW
  , dynamic_read = GL_DYNAMIC_READ
  , dynamic_copy = GL_DYNAMIC_COPY
};

}}}

#endif // SCENER_GRAPHICS_OPENGL_BUFFERUSAGE_HPP
