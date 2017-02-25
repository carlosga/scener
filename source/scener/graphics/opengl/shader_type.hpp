// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_OPENGL_SHADER_TYPE_HPP
#define SCENER_GRAPHICS_OPENGL_SHADER_TYPE_HPP

#include <cstdint>

#include "scener/graphics/opengl/platform.hpp"

namespace scener::graphics::opengl
{
    /// Declares the supported shader types.
    enum class shader_type : std::uint32_t
    {
        vertex          = GL_VERTEX_SHADER          ///< A shader that is intended to run on the programmable vertex processor.
    , tess_control    = GL_TESS_CONTROL_SHADER    ///< A shader that is intended to run on the programmable tessellation processor in the control stage.
    , tess_evaluation = GL_TESS_EVALUATION_SHADER ///< A shader that is intended to run on the programmable tessellation processor in the evaluation stage.
    , geometry        = GL_GEOMETRY_SHADER        ///< A shader that is intended to run on the programmable geometry processor.
    , fragment        = GL_FRAGMENT_SHADER        ///< A shader that is intended to run on the programmable fragment processor.
    };
}

#endif // SCENER_GRAPHICS_OPENGL_SHADER_TYPE_HPP
