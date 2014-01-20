//-------------------------------------------------------------------------------
//Copyright 2013 Carlos Guzmán Álvarez
//
//Licensed under the Apache License, Version 2.0 (the "License");
//you may not use this file except in compliance with the License.
//You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//Unless required by applicable law or agreed to in writing, software
//distributed under the License is distributed on an "AS IS" BASIS,
//WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//See the License for the specific language governing permissions and
//limitations under the License.
//-------------------------------------------------------------------------------

#ifndef BUFFERTARGET_HPP
#define BUFFERTARGET_HPP

#include <System/Core.hpp>
#include <System/Graphics/Platform.hpp>

namespace SceneR
{
    namespace Graphics
    {
        /**
         * Defines opengl buffer object targets
         */
        enum class BufferTarget : System::UInt32
        {
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
    }
}

#endif // BUFFERTARGET_HPP
