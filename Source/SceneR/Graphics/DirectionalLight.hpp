// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_DIRECTIONALLIGHT_HPP
#define SCENER_GRAPHICS_DIRECTIONALLIGHT_HPP

#include "SceneR/Math/Vector3.hpp"

namespace SceneR { namespace Graphics {

/**
 * Light object that projects its effect along a direction specified by a Vector3.
 */
class DirectionalLight
{
public:
    /**
     * Creates an instance of a light that projects its effect in a specified direction.
     * This contructor creates an instance of a white light projected along a Vector3 of value (0, 0, -1).
     */
    DirectionalLight() noexcept;

    /**
     * Creates an instance of a light that projects its effect along a specified Vector3 with a specified color.
     * @param direction the direction of the new light.
     * @param diffuseColor diffuse color of the new light.
     * @param specularColor specular color of the new light.
     */
    DirectionalLight(const SceneR::Math::Vector3& direction
                   , const SceneR::Math::Vector3& diffuseColor
                   , const SceneR::Math::Vector3& specularColor) noexcept;

    /**
     * Copy constructor.
     */
    DirectionalLight(const DirectionalLight& light) = default;

    /**
     * Releases all resources being used by this DirectionalLight.
     */
    ~DirectionalLight() = default;

public:
     DirectionalLight& operator=(const DirectionalLight& light) = default;

public:
    SceneR::Math::Vector3 _direction;
    SceneR::Math::Vector3 _diffuse_color;
    SceneR::Math::Vector3 _specular_color;
    bool                  _enabled;
};

}}

#endif // SCENER_GRAPHICS_DIRECTIONALLIGHT_HPP
