// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_VERTEXELEMENTUSAGE_HPP
#define SCENER_GRAPHICS_VERTEXELEMENTUSAGE_HPP

#include <cstdint>

namespace scener { namespace graphics {

/// Defines usage for vertex elements.
enum class vertex_element_usage : std::uint32_t
{
    position           =  0 ///< Position data.
  , color              =  1 ///< Vertex data contains diffuse or specular color.
  , texture_coordinate =  2 ///< Texture coordinate data.
  , normal             =  3 ///< Vertex normal data.
  , binormal           =  4 ///< Vertex binormal data.
  , tangent            =  5 ///< Vertex tangent data.
  , blend_indices      =  6 ///< Blending indices data.
  , blend_weight       =  7 ///< Blending weight data.
  , depth              =  8 ///< Vertex data contains depth data.
  , fog                =  9 ///< Vertex data contains fog data.
  , point_size         = 10 ///< Point size data.
  , sample             = 11 ///< Vertex data contains sampler data.
  , tessellate_factor  = 12 ///< Single, positive floating-point value.
};

}}

#endif // SCENER_GRAPHICS_VERTEXELEMENTUSAGE_HPP
