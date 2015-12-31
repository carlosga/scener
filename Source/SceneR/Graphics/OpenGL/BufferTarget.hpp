// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_OPENGL_BUFFERTARGET_HPP
#define SCENER_GRAPHICS_OPENGL_BUFFERTARGET_HPP

#include <cstdint>

#include "SceneR/Graphics/OpenGL/glad.hpp"

namespace SceneR { namespace Graphics { namespace OpenGL {

/**
 * Defines opengl buffer object targets
 */
enum class BufferTarget : std::uint32_t
{
    /**
     * GLTF Buffer used for animation or skin data.
     */
    animation_or_skin = 0,
    /**
     * A buffer used as a source for vertex data.
     */
    array_buffer = GL_ARRAY_BUFFER,
    /**
     * An indexed buffer binding for buffers used as storage for atomic counters
     */
    atomic_counter_bufer = GL_ATOMIC_COUNTER_BUFFER,
    /**
     * A buffer for reading buffer object data.
     */
    copy_read_buffer = GL_COPY_READ_BUFFER,
    /**
     * A buffer for writing buffer object data.
     */
    copy_write_buffer = GL_COPY_WRITE_BUFFER,
    /**
     * A buffer used as the source for the indirect data when performing indirect rendering.
     */
    draw_indirect_buffer = GL_DRAW_INDIRECT_BUFFER,
    /**
     * A buffer used as the source for indirect compute dispatch operations.
     */
    dispatch_indirect_buffer = GL_DISPATCH_INDIRECT_BUFFER,
    /**
     * A buffer used as the source of the indices used for indexed rendering.
     */
    element_array_buffer = GL_ELEMENT_ARRAY_BUFFER,
    /**
     * A buffer used for performing asynchronous pixel transfer operations.
     */
    pixel_pack_buffer = GL_PIXEL_PACK_BUFFER,
    /**
     * A buffer used for performing asynchronous pixel transfer operations.
     */
    pixel_unpack_buffer = GL_PIXEL_UNPACK_BUFFER,
    /**
     * An indexed buffer used as storage for shader storage blocks.
     */
    shader_storage_buffer = GL_SHADER_STORAGE_BUFFER,
    /**
     * A buffer used as as storage for textures.
     */
    texture_buffer = GL_TEXTURE_BUFFER,
    /**
     * An indexed buffer binding used for transform feedback operations.
     */
    transform_feedback_buffer = GL_TRANSFORM_FEEDBACK_BUFFER,
    /**
     * An indexed buffer binding used as storage for uniform blocks.
     */
    uniform_buffer = GL_UNIFORM_BUFFER
};

}}}

#endif // SCENER_GRAPHICS_OPENGL_BUFFERTARGET_HPP
