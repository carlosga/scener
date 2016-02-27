// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_EFFECTPARAMETERTYPE_HPP
#define SCENER_GRAPHICS_EFFECTPARAMETERTYPE_HPP

#include <cstdint>

namespace scener { namespace graphics {

/// Defines types that can be used for effect parameters or shader constants.
enum class effect_parameter_type : std::uint32_t
{
    boolean      = 1    ///< Parameter is a Boolean.
  , byte         = 2    ///< Parameter is a signed byte.
  , ubyte        = 3    ///< Parameter is an unsigned byte.
  , int16        = 4    ///< Parameter is an signed 16-bit integer.
  , uint16       = 5    ///< Parameter is an unsigned 16-bit integer.
  , int32        = 6    ///< Parameter is an signed 32-bit integer.
  , uint32       = 7    ///< Parameter is an unsigned 32-bit integer.
  , single       = 8    ///< Parameter is a floating-point number.
  , string       = 9    ///< Parameter is a string.
  , texture      = 10   ///< Parameter is a texture.
  , texture_1d   = 11   ///< Parameter is a 1D texture.
  , texture_2d   = 12   ///< Parameter is a 2D texture.
  , texture_3d   = 13   ///< Parameter is a 3D texture.
  , texture_cube = 14   ///< Parameter is a cube texture.
  , void_pointer = 15   ///< Parameter is a void pointer.
};

}}

#endif // SCENER_GRAPHICS_EFFECTPARAMETERTYPE_HPP
