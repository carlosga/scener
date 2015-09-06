// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/DirectionalLight.hpp>

namespace SceneR
{
    namespace Graphics
    {
        using SceneR::Framework::Vector3;

        DirectionalLight::DirectionalLight()
            : DirectionalLight { { 0.0f, -1.0f, 0.0f }, Vector3::one, Vector3::zero }
        {
        }

        DirectionalLight::DirectionalLight(const Vector3& direction
                                         , const Vector3& diffuseColor
                                         , const Vector3& specularColor)
            : direction      { direction }
            , diffuse_color  { diffuseColor }
            , specular_color { specularColor }
            , enabled        { false }
        {
        }

        DirectionalLight::DirectionalLight(const DirectionalLight& light)
            : direction      { light.direction }
            , diffuse_color  { light.diffuse_color }
            , specular_color { light.specular_color }
            , enabled        { light.enabled }
        {
        }

        DirectionalLight::~DirectionalLight()
        {
        }

        DirectionalLight&DirectionalLight::operator=(const DirectionalLight& light)
        {
            if (this != &light)
            {
                this->direction      = light.direction;
                this->diffuse_color  = light.diffuse_color;
                this->specular_color = light.specular_color;
                this->enabled        = light.enabled;
            }

            return *this;
        }
    }
}
