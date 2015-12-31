// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_EFFECTPARAMETERCLASS_HPP
#define SCENER_GRAPHICS_EFFECTPARAMETERCLASS_HPP

#include <cstdint>

namespace SceneR { namespace Graphics {

/**
 * Defines classes that can be used for effect parameters or shader constants.
 */
enum class EffectParameterClass : std::uint32_t
{
    /**
     * Constant is a matrix.
     */
    matrix = 1,
    /**
     * Constant is either a texture, a shader, or a string.
     */
    object = 2,
    /**
     * Constant is a scalar.
     */
    scalar = 3,
    /**
     * Constant is a structure.
     */
    structure = 4,
    /**
     * Constant is a vector.
     */
    vector = 5
};

}}

#endif // SCENER_GRAPHICS_EFFECTPARAMETERCLASS_HPP
