// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_DIRECTIONALLIGHT_HPP
#define SCENER_GRAPHICS_DIRECTIONALLIGHT_HPP

#include "scener/math/vector.hpp"

namespace scener { namespace graphics {

/// Light object that projects its effect along a direction specified by a vector3.
class directional_light final
{
public:
    /// Creates an instance of a light that projects its effect in a specified direction.
    /// This contructor creates an instance of a white light projected along a vector3 of value (0, 0, -1).
    directional_light() noexcept;

    /// Creates an instance of a light that projects its effect along a specified vector3 with a specified color.
    /// \param lightDirection the direction of the new light.
    /// \param diffuseColor diffuse color of the new light.
    /// \param specularColor specular color of the new light.
    directional_light(const scener::math::vector3& lightDirection
                   , const scener::math::vector3& diffuseColor
                   , const scener::math::vector3& specularColor) noexcept;

public:
    scener::math::vector3 direction;        ///< Gets or sets the light direction. This value must be a unit vector.
    scener::math::vector3 diffuse_color;    ///< Gets or sets the diffuse color of the light.
    scener::math::vector3 specular_color;   ///< Gets or sets the specular color of the light.
    bool                  enabled;          ///< Gets or sets light enable flag.
};

}}

#endif // SCENER_GRAPHICS_DIRECTIONALLIGHT_HPP
