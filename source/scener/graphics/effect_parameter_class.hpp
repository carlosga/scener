// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_EFFECT_PARAMETER_CLASS_HPP
#define SCENER_GRAPHICS_EFFECT_PARAMETER_CLASS_HPP

#include <cstdint>

namespace scener::graphics
{
    /// Defines classes that can be used for effect parameters or shader constants.
    enum class effect_parameter_class : std::uint32_t
    {
        matrix    = 1   ///< Constant is a matrix.
      , object    = 2   ///< Constant is either a texture, a shader, or a string.
      , scalar    = 3   ///< Constant is a scalar.
      , structure = 4   ///< Constant is a structure.
      , vector    = 5   ///< Constant is a vector.
    };
}

#endif // SCENER_GRAPHICS_EFFECT_PARAMETER_CLASS_HPP
