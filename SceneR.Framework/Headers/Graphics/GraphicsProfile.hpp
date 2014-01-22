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

#ifndef GRAPHICSPROFILE_HPP
#define GRAPHICSPROFILE_HPP

#include <System/Core.hpp>
#include <System/Graphics/Platform.hpp>

namespace SceneR
{
    namespace Graphics
    {
        /**
         * Identifies the type of OpenGL profile to be used on GraphicsDevice instances.
         */
        enum class GraphicsProfile : System::UInt32
        {
            /**
             * Core profile
             */
            HiDef = GLFW_OPENGL_CORE_PROFILE,
            /**
             * Compatibility profile
             */
            Reach = GLFW_OPENGL_COMPAT_PROFILE
        };
    }
}

#endif  /* GRAPHICSPROFILE_HPP */
