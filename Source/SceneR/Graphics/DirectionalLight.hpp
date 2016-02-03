// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_DIRECTIONALLIGHT_HPP
#define SCENER_GRAPHICS_DIRECTIONALLIGHT_HPP

#include "SceneR/Math/Vector3.hpp"

namespace SceneR { namespace Graphics {

/// Light object that projects its effect along a direction specified by a Vector3.
class DirectionalLight
{
public:
    /// Creates an instance of a light that projects its effect in a specified direction.
    /// This contructor creates an instance of a white light projected along a Vector3 of value (0, 0, -1).
    DirectionalLight() noexcept;

    /// Creates an instance of a light that projects its effect along a specified Vector3 with a specified color.
    /// \param direction the direction of the new light.
    /// \param diffuseColor diffuse color of the new light.
    /// \param specularColor specular color of the new light.
    DirectionalLight(const SceneR::Math::Vector3& direction
                   , const SceneR::Math::Vector3& diffuseColor
                   , const SceneR::Math::Vector3& specularColor) noexcept;

public:
    SceneR::Math::Vector3 direction;        ///< Gets or sets the light direction. This value must be a unit vector.
    SceneR::Math::Vector3 diffuse_color;    ///< Gets or sets the diffuse color of the light.
    SceneR::Math::Vector3 specular_color;   ///< Gets or sets the specular color of the light.
    bool                  enabled;          ///< Gets or sets light enable flag.
};

}}

#endif // SCENER_GRAPHICS_DIRECTIONALLIGHT_HPP
