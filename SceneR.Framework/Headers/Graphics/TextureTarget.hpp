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

#ifndef TEXTURETARGET_HPP
#define TEXTURETARGET_HPP

#include <GL/glew.h>
#include <System/Core.hpp>

namespace SceneR
{
    namespace Graphics
    {
        /**
         * Declares OpenGL texture targets
         */
        enum class TextureTarget : System::UInt32
        {
            Texture1D                 = GL_TEXTURE_1D,
            Texture2D                 = GL_TEXTURE_2D,
            Texture3D                 = GL_TEXTURE_3D,
            Texture1DArray            = GL_TEXTURE_1D_ARRAY,
            Texture2DArray            = GL_TEXTURE_2D_ARRAY,
            TextureRect               = GL_TEXTURE_RECTANGLE,
            TextureCubeMap            = GL_TEXTURE_CUBE_MAP,
            TextureCubeMapArray       = GL_TEXTURE_CUBE_MAP_ARRAY,
            TextureBuffer             = GL_TEXTURE_BUFFER,
            Texture2DMultiSample      = GL_TEXTURE_2D_MULTISAMPLE,
            Texture2DMultiSampleArray = GL_TEXTURE_2D_MULTISAMPLE_ARRAY
        };
    }
}


#endif /* TEXTURETARGET_HPP */
