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

#ifndef CONTENTTYPE_HPP
#define	CONTENTTYPE_HPP

#include "Core/Core.hpp"

namespace SceneR
{
    namespace Content
    {
        /**
         * Types of content supported
         */
        enum class ContentType : UInt32
        {
            AlphaTextEffect      = 0,
            BasicEffect          = 1,
            DualTextureEffect    = 2,
            EnvironmentMapEffect = 3,
            Effect               = 4,
            EffectMaterial       = 5,
            IndexBuffer          = 6,
            Model                = 7,
            SkinnedEffect        = 8,
            Texture2D            = 9,
            Texture3D            = 10,
            TextureCube          = 11,
            VertextBuffer        = 12,
            VertexDeclaration    = 13
        };
    }
}

#endif	/* CONTENTTYPE_HPP */

