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

#ifndef VERTEXBUFFERTARGET_HPP
#define VERTEXBUFFERTARGET_HPP

#include <GL/glew.h>
#include <System/Core.hpp>

namespace SceneR
{
    namespace Graphics
    {
        enum class BufferTarget : System::UInt32
        {
            ArrayBuffer              = GL_ARRAY_BUFFER,
            AtomicCounterBufer       = GL_ATOMIC_COUNTER_BUFFER,
            CopyReadBuffer           = GL_COPY_READ_BUFFER,
            CopyWriteBuffer          = GL_COPY_WRITE_BUFFER,
            DrawIndirectBuffer       = GL_DRAW_INDIRECT_BUFFER,
            DispatchIndirectBuffer   = GL_DISPATCH_INDIRECT_BUFFER,
            ElementArraybuffer       = GL_ELEMENT_ARRAY_BUFFER,
            PixelPackBuffer          = GL_PIXEL_PACK_BUFFER,
            PixelUnpackBuffer        = GL_PIXEL_UNPACK_BUFFER,
            ShaderStorageBuffer      = GL_SHADER_STORAGE_BUFFER,
            TextureBuffer            = GL_TEXTURE_BUFFER,
            TransformFeedbackBuffer  = GL_TRANSFORM_FEEDBACK_BUFFER,
            UniformBuffer            = GL_UNIFORM_BUFFER
        };
    }
}

#endif // VERTEXBUFFERTARGET_HPP
