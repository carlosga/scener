// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SceneR/Graphics/DirectionalLight.hpp"

namespace scener { namespace graphics {

using scener::math::vector3;

DirectionalLight::DirectionalLight() noexcept
    : DirectionalLight { { 0.0f, -1.0f, 0.0f }, vector3::one(), vector3::zero() }
{
}

DirectionalLight::DirectionalLight(const vector3& lightDirection
                                 , const vector3& diffuseColor
                                 , const vector3& specularColor) noexcept
    : direction      { lightDirection }
    , diffuse_color  { diffuseColor }
    , specular_color { specularColor }
    , enabled        { false }
{
}

}}
