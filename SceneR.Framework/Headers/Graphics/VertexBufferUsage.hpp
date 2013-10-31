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

#ifndef VERTEXBUFFERUSAGE_HPP
#define VERTEXBUFFERUSAGE_HPP

#include <GL/glew.h>
#include <System/Core.hpp>

namespace SceneR
{
    namespace Graphics
    {
        enum class VertexBufferUsage : UInt32
        {
            StreamDraw  = GL_STREAM_DRAW,
            StreamReade = GL_STREAM_READ,
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

#endif // VERTEXBUFFERUSAGE_HPP
