// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef GRAPHICSPROFILE_HPP
#define GRAPHICSPROFILE_HPP

#include <System/Graphics/Platform.hpp>
#include <System/Core.hpp>

namespace SceneR
{
    namespace Graphics
    {
        /**
         * Identifies the type of OpenGL profile to be used on GraphicsDevice instances.
         */
        enum class GraphicsProfile : uint32_t
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
