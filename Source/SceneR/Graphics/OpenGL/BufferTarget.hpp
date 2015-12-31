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
    AnimationOrSkin = 0,
    /**
     * A buffer used as a source for vertex data.
     */
    ArrayBuffer = GL_ARRAY_BUFFER,
    /**
     * An indexed buffer binding for buffers used as storage for atomic counters
     */
    AtomicCounterBufer = GL_ATOMIC_COUNTER_BUFFER,
    /**
     * A buffer for reading buffer object data.
     */
    CopyReadBuffer = GL_COPY_READ_BUFFER,
    /**
     * A buffer for writing buffer object data.
     */
    CopyWriteBuffer = GL_COPY_WRITE_BUFFER,
    /**
     * A buffer used as the source for the indirect data when performing indirect rendering.
     */
    DrawIndirectBuffer = GL_DRAW_INDIRECT_BUFFER,
    /**
     * A buffer used as the source for indirect compute dispatch operations.
     */
    DispatchIndirectBuffer = GL_DISPATCH_INDIRECT_BUFFER,
    /**
     * A buffer used as the source of the indices used for indexed rendering.
     */
    ElementArraybuffer = GL_ELEMENT_ARRAY_BUFFER,
    /**
     * A buffer used for performing asynchronous pixel transfer operations.
     */
    PixelPackBuffer = GL_PIXEL_PACK_BUFFER,
    /**
     * A buffer used for performing asynchronous pixel transfer operations.
     */
    PixelUnpackBuffer = GL_PIXEL_UNPACK_BUFFER,
    /**
     * An indexed buffer used as storage for shader storage blocks.
     */
    ShaderStorageBuffer = GL_SHADER_STORAGE_BUFFER,
    /**
     * A buffer used as as storage for textures.
     */
    TextureBuffer = GL_TEXTURE_BUFFER,
    /**
     * An indexed buffer binding used for transform feedback operations.
     */
    TransformFeedbackBuffer = GL_TRANSFORM_FEEDBACK_BUFFER,
    /**
     * An indexed buffer binding used as storage for uniform blocks.
     */
    UniformBuffer = GL_UNIFORM_BUFFER
};

}}}

#endif // SCENER_GRAPHICS_OPENGL_BUFFERTARGET_HPP
