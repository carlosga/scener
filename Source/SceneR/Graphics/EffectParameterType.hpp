// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_EFFECTPARAMETERTYPE_HPP
#define SCENER_GRAPHICS_EFFECTPARAMETERTYPE_HPP

#include <cstdint>

namespace SceneR { namespace Graphics {

/**
 * Defines types that can be used for effect parameters or shader constants.
 */
enum class EffectParameterType : std::uint32_t
{
    /**
     * Parameter is a Boolean. Any nonzero value passed in will be mapped to 1 (TRUE)
     * before being written into the constant table; otherwise, the value will be set to 0 in the constant
     * table.
     */
    boolean = 1,
    /**
     * Parameter is a signed byte. Any floating-point values passed in will be rounded off
     * (to zero decimal places) before being written into the constant table.
     */
    byte = 2,
    /**
     * Parameter is an unsigned byte. Any floating-point values passed in will be rounded off
     * (to zero decimal places) before being written into the constant table.
     */
    ubyte = 3,
    /**
     * Parameter is an signed 16-bit integer. Any floating-point values passed in will be rounded off
     * (to zero decimal places) before being written into the constant table.
     */
    int16 = 4,
    /**
     * Parameter is an unsigned 16-bit integer. Any floating-point values passed in will be rounded off
     * (to zero decimal places) before being written into the constant table.
     */
    uint16 = 5,
    /**
     * Parameter is an signed 32-bit integer. Any floating-point values passed in will be rounded off
     * (to zero decimal places) before being written into the constant table.
     */
    int32 = 6,
    /**
     * Parameter is an unsigned 32-bit integer. Any floating-point values passed in will be rounded off
     * (to zero decimal places) before being written into the constant table.
     */
    uint32 = 7,
    /**
     * Parameter is a floating-point number.
     */
    single = 8,
    /**
     * Parameter is a string.
     */
    string = 9,
    /**
     * Parameter is a texture.
     */
    texture = 10,
    /**
     * Parameter is a 1D texture.
     */
    texture_1d = 11,
    /**
     * Parameter is a 2D texture.
     */
    texture_2d = 12,
    /**
     * Parameter is a 3D texture.
     */
    texture_3d = 13,
    /**
     * Parameter is a cube texture.
     */
    texture_cube = 14,
    /**
     * Parameter is a void pointer.
     */
    void_pointer = 15
};

}}

#endif // SCENER_GRAPHICS_EFFECTPARAMETERTYPE_HPP
