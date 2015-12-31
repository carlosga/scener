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
    Position = 0,
    /**
     * Vertex data contains diffuse or specular color.
     */
    Color = 1,
    /**
     * Texture coordinate data.
     */
    TextureCoordinate = 2,
    /**
     * Vertex normal data.
     */
    Normal = 3,
    /**
     * Vertex binormal data.
     */
    Binormal = 4,
    /**
     * Vertex tangent data.
     */
    Tangent = 5,
    /**
     * Blending indices data.
     */
    BlendIndices = 6,
    /**
     * Blending weight data.
     */
    BlendWeight = 7,
    /**
     * Vertex data contains depth data.
     */
    Depth = 8,
    /**
     * Vertex data contains fog data.
     */
    Fog = 9,
    /**
     * Point size data.
     */
    PointSize = 10,
    /**
     * Vertex data contains sampler data.
     */
    Sample = 11,
    /**
     * Single, positive floating-point value.
     */
    TessellateFactor = 12
};

}}

#endif // SCENER_GRAPHICS_VERTEXELEMENTUSAGE_HPP
