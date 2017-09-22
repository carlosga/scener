// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_VULKAN_BUFFER_TARGET_HPP
#define SCENER_GRAPHICS_VULKAN_BUFFER_TARGET_HPP

#include <cstdint>

namespace scener::graphics::vulkan
{
    /// Defines opengl buffer object targets
    enum class buffer_target : std::uint32_t
    {
        animation_or_skin     = 0       ///< GLTF Buffer used for animation or skin data.
      , shader_storage_buffer = 0x90D2  ///< An indexed buffer used as storage for shader storage blocks.
      , texture_buffer        = 0x8C2A  ///< A buffer used as as storage for textures.
      , uniform_buffer        = 0x8A11  ///< An indexed buffer binding used as storage for uniform blocks.
      , vertex_buffer         = 0x8892  ///< A buffer used as a source for vertex data.
      , index_buffer          = 0x8893  ///< A buffer used as the source of the indices used for indexed rendering.
    };
}

#endif // SCENER_GRAPHICS_VULKAN_BUFFER_TARGET_HPP
