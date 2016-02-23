// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SceneR/Graphics/DirectionalLight.hpp"

namespace SceneR { namespace Graphics {

using SceneR::Math::Vector3;

DirectionalLight::DirectionalLight() noexcept
    : DirectionalLight { { 0.0f, -1.0f, 0.0f }, Vector3::one, Vector3::zero }
{
}

DirectionalLight::DirectionalLight(const Vector3& lightDirection
                                 , const Vector3& diffuseColor
                                 , const Vector3& specularColor) noexcept
    : direction      { lightDirection }
    , diffuse_color  { diffuseColor }
    , specular_color { specularColor }
    , enabled        { false }
{
}

}}
