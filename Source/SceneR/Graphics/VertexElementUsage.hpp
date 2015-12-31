// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_VERTEXELEMENTUSAGE_HPP
#define SCENER_GRAPHICS_VERTEXELEMENTUSAGE_HPP

#include <cstdint>

namespace SceneR { namespace Graphics {

/**
 * Defines usage for vertex elements.
 */
enum class VertexElementUsage : std::uint32_t
{
    /**
     * Position data.
     */
    position = 0,
    /**
     * Vertex data contains diffuse or specular color.
     */
    color = 1,
    /**
     * Texture coordinate data.
     */
    texture_coordinate = 2,
    /**
     * Vertex normal data.
     */
    normal = 3,
    /**
     * Vertex binormal data.
     */
    binormal = 4,
    /**
     * Vertex tangent data.
     */
    tangent = 5,
    /**
     * Blending indices data.
     */
    blend_indices = 6,
    /**
     * Blending weight data.
     */
    blend_weight = 7,
    /**
     * Vertex data contains depth data.
     */
    depth = 8,
    /**
     * Vertex data contains fog data.
     */
    fog = 9,
    /**
     * Point size data.
     */
    point_size = 10,
    /**
     * Vertex data contains sampler data.
     */
    sample = 11,
    /**
     * Single, positive floating-point value.
     */
    tessellate_factor = 12
};

}}

#endif // SCENER_GRAPHICS_VERTEXELEMENTUSAGE_HPP
