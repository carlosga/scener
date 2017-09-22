// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_VULKAN_SHADER_STAGE_HPP
#define SCENER_GRAPHICS_VULKAN_SHADER_STAGE_HPP

#include <cstdint>

namespace scener::graphics::vulkan
{
    /// Declares the supported shader stages.
    enum class shader_stage : std::uint32_t
    {
        vertex          = 0x00000001  ///< A shader that is intended to run on the programmable vertex processor.
      , tess_control    = 0x00000002  ///< A shader that is intended to run on the programmable tessellation processor in the control stage.
      , tess_evaluation = 0x00000004  ///< A shader that is intended to run on the programmable tessellation processor in the evaluation stage.
      , geometry        = 0x00000008  ///< A shader that is intended to run on the programmable geometry processor.
      , fragment        = 0x00000010  ///< A shader that is intended to run on the programmable fragment processor.
      , compute         = 0x00000020  ///< A shader that is intended to run on the programmable compute processor.
      , all_graphics    = 0x0000001F
      , all             = 0x7FFFFFFF
    };
}

#endif // SCENER_GRAPHICS_VULKAN_SHADER_STAGE_HPP
