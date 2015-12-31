// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_VERTEXELEMENTFORMAT_HPP
#define SCENER_GRAPHICS_VERTEXELEMENTFORMAT_HPP

#include <cstdint>

namespace SceneR { namespace Graphics {

/**
 * Defines vertex element formats.
 */
enum class VertexElementFormat : std::uint32_t
{
    /**
     * Single-component, 32-bit floating-point, expanded to (float, 0, 0, 1).
     */
    single = 0,
    /**
     * Two-component, 32-bit floating-point, expanded to (float, float, 0, 1).
     */
    vector2 = 1,
    /**
     * Three-component, 32-bit floating point, expanded to (float, float, float, 1).
     */
    vector3 = 2,
    /**
     * Four-component, 32-bit floating point, expanded to (float, float, float, float).
     */
    vector4 = 3,
    /**
     * Four-component, packed, unsigned byte, mapped to 0 to 1 range.
     * Input is in Int32 format (ARGB) expanded to (R, G, B, A).
     */
    color = 4,
    /**
     * Four-component, unsigned byte.
     */
    byte4 = 5,
    /**
     * Two-component, signed short expanded to (value, value, 0, 1).
     */
    short2 = 6,
    /**
     * Four-component, signed short expanded to (value, value, value, value).
     */
    short4 = 7,
    /**
     * Normalized, two-component, signed short, expanded to (first short/32767.0, second short/32767.0, 0, 1).
     */
    normalized_short2 = 8,
    /**
     * Normalized, four-component, signed short, expanded to (first short/32767.0, second short/32767.0,
     * third short/32767.0, fourth short/32767.0).
     */
    normalized_short4 = 9,
    /**
     * Two-component, 16-bit floating point expanded to (value, value, value, value).
     */
    half_vector2 = 10,
    /**
     * Four-component, 16-bit floating-point expanded to (value, value, value, value).
     */
    half_vector4 = 11
};

}}

#endif // SCENER_GRAPHICS_VERTEXELEMENTFORMAT_HPP
