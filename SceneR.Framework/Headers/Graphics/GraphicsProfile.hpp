// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef GRAPHICS_GRAPHICSPROFILE_HPP
#define GRAPHICS_GRAPHICSPROFILE_HPP

#include <cstdint>

#include <System/Graphics/Platform.hpp>

namespace SceneR
{
    namespace Graphics
    {
        /**
         * Identifies the type of OpenGL profile to be used on GraphicsDevice instances.
         */
        enum class GraphicsProfile : std::uint32_t
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

#endif  // GRAPHICS_GRAPHICSPROFILE_HPP
