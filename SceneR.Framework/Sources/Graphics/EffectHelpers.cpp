// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
//---------------------------------------------------------------------------------------------------
// Ported from Microsoft XNA Community Game Platform Stock Effects
//---------------------------------------------------------------------------------------------------
// Microsoft XNA Community Game Platform
// Copyright (C) Microsoft Corporation. All rights reserved.
//---------------------------------------------------------------------------------------------------

#include <Graphics/EffectHelpers.hpp>

#include <Framework/Matrix.hpp>
#include <Framework/Vector3.hpp>
#include <Framework/Vector4.hpp>
#include <Graphics/DirectionalLight.hpp>
#include <Graphics/EffectParameter.hpp>
#include <System/Math.hpp>

namespace SceneR
{
    namespace Graphics
    {
        using SceneR::Framework::Matrix;
        using SceneR::Framework::Vector3;
        using SceneR::Framework::Vector4;
        using System::Math;

        Vector3 EffectHelpers::enable_default_lighting(DirectionalLight& light0
                                                     , DirectionalLight& light1
                                                     , DirectionalLight& light2)
        {
            // Key light.
            light0.direction      = { -0.5265408f, -0.5735765f, -0.6275069f };
            light0.diffuse_color  = { 1.0f, 0.9607844f, 0.8078432f };
            light0.specular_color = { 1.0f, 0.9607844f, 0.8078432f };
            light0.enabled        = true;

            // Fill light.
            light1.direction      = { 0.7198464f, 0.3420201f, 0.6040227f };
            light1.diffuse_color  = { 0.9647059f, 0.7607844f, 0.4078432f };
            light1.specular_color = Vector3::zero;
            light1.enabled        = true;

            // Back light.
            light2.direction      = { 0.4545195f, -0.7660444f, 0.4545195f };
            light2.diffuse_color  = { 0.3231373f, 0.3607844f, 0.3937255f };
            light2.specular_color = { 0.3231373f, 0.3607844f, 0.3937255f };
            light1.enabled        = true;

            return { 0.05333332f, 0.09882354f, 0.1819608f };
        }

        EffectDirtyFlags EffectHelpers::set_world_view_proj(const EffectDirtyFlags&          dirtyFlags
                                                          , const Matrix&                    world
                                                          , const Matrix&                    view
                                                          , const Matrix&                    projection
                                                          , Matrix&                          worldView
                                                          , std::shared_ptr<EffectParameter> worldViewProjParam)
        {
            auto result = dirtyFlags;

            // Recompute the world+view+projection matrix?
            if ((dirtyFlags & EffectDirtyFlags::WorldViewProj) != 0)
            {
                Matrix worldViewProj;

                worldView     = world * view;
                worldViewProj = worldView * projection;

                worldViewProjParam->set_value_transpose<Matrix>(worldViewProj);

                result &= ~EffectDirtyFlags::WorldViewProj;
            }

            return result;
        }

        void EffectHelpers::set_fog_vector(const Matrix&                    worldView
                                         , const float&                     fogStart
                                         , const float&                     fogEnd
                                         , std::shared_ptr<EffectParameter> fogVectorParam)
        {
            if (Math::equal(fogStart, fogEnd))
            {
                // Degenerate case: force everything to 100% fogged if start and end are the same.
                fogVectorParam->set_value<Vector4>({ 0.0f, 0.0f, 0.0f, 1.0f });
            }
            else
            {
                // We want to transform vertex positions into view space, take the resulting
                // Z value, then scale and offset according to the fog start/end distances.
                // Because we only care about the Z component, the shader can do all this
                // with a float dot product, using only the Z row of the world+view matrix.

                float scale = 1.0f / (fogStart - fogEnd);

                fogVectorParam->set_value<Vector4>({  worldView.m13 * scale
                                                   ,  worldView.m23 * scale
                                                   ,  worldView.m33 * scale
                                                   , (worldView.m43 + fogStart) * scale });
            }
        }

        EffectDirtyFlags EffectHelpers::set_lighting_matrices(const EffectDirtyFlags&          dirtyFlags
                                                            , const Matrix&                    world
                                                            , const Matrix&                    view
                                                            , std::shared_ptr<EffectParameter> worldParam
                                                            , std::shared_ptr<EffectParameter> worldInverseTransposeParam
                                                            , std::shared_ptr<EffectParameter> eyePositionParam)
        {
            auto result = dirtyFlags;

            // Set the world and world inverse transpose matrices.
            if ((dirtyFlags & EffectDirtyFlags::World) != 0)
            {
                auto worldTranspose        = Matrix::invert(world);
                auto worldInverseTranspose = Matrix::transpose(worldTranspose);

                worldParam->set_value<Matrix>(world);
                worldInverseTransposeParam->set_value_transpose<Matrix>(worldInverseTranspose);

                result &= ~EffectDirtyFlags::World;
            }

            // Set the eye position.
            if (eyePositionParam != nullptr)
            {
                if ((dirtyFlags & EffectDirtyFlags::EyePosition) != 0)
                {
                    auto viewInverse = Matrix::invert(view);

                    eyePositionParam->set_value<Vector3>(viewInverse.translation());

                    result &= ~EffectDirtyFlags::EyePosition;
                }
            }

            return result;
        }

        void EffectHelpers::set_material_color(const bool&                      lightingEnabled
                                             , const float&                     alpha
                                             , const Vector3&                   diffuseColor
                                             , const Vector3&                   emissiveColor
                                             , const Vector3&                   ambientLightColor
                                             , std::shared_ptr<EffectParameter> diffuseColorParam
                                             , std::shared_ptr<EffectParameter> emissiveColorParam)
        {
            // Desired lighting model:
            //
            //     ((AmbientLightColor + sum(diffuse directional light)) * DiffuseColor) + EmissiveColor
            //
            // When lighting is disabled, ambient and directional lights are ignored, leaving:
            //
            //     DiffuseColor + EmissiveColor
            //
            // For the lighting disabled case, we can save one shader instruction by precomputing
            // diffuse+emissive on the CPU, after which the shader can use DiffuseColor directly,
            // ignoring its emissive parameter.
            //
            // When lighting is enabled, we can merge the ambient and emissive settings. If we
            // set our emissive parameter to emissive+(ambient*diffuse), the shader no longer
            // needs to bother adding the ambient contribution, simplifying its computation to:
            //
            //     (sum(diffuse directional light) * DiffuseColor) + EmissiveColor
            //
            // For futher optimization goodness, we merge material alpha with the diffuse
            // color parameter, and premultiply all color values by this alpha.

            if (lightingEnabled)
            {
                diffuseColorParam->set_value<Vector4>({ diffuseColor * alpha, alpha });
                emissiveColorParam->set_value<Vector3>({ (emissiveColor + ambientLightColor * diffuseColor) * alpha });
            }
            else
            {
                diffuseColorParam->set_value<Vector4>({ (diffuseColor + emissiveColor) * alpha, alpha });
            }
        }
    }
}
