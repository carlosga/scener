// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
//---------------------------------------------------------------------------------------------------
// Ported from Microsoft XNA Community Game Platform Stock Effects
//---------------------------------------------------------------------------------------------------
// Microsoft XNA Community Game Platform
// Copyright (C) Microsoft Corporation. All rights reserved.
//---------------------------------------------------------------------------------------------------

#include <Graphics/EffectHelpers.hpp>

#include <System/Math.hpp>
#include <Framework/Matrix.hpp>
#include <Framework/Vector3.hpp>
#include <Framework/Vector4.hpp>
#include <Graphics/DirectionalLight.hpp>

namespace SceneR
{
    namespace Graphics
    {
        using System::Math;
        using SceneR::Framework::Matrix;
        using SceneR::Framework::Vector3;
        using SceneR::Framework::Vector4;

        Vector3 EffectHelpers::enable_default_lighting(DirectionalLight &light0, DirectionalLight &light1,
                                                       DirectionalLight &light2)
        {
            // Key light.
            light0.direction      = { -0.5265408f, -0.5735765f, -0.6275069f };
            light0.diffuse_color  = { 1.0f, 0.9607844f, 0.8078432f };
            light0.specular_color = { 1.0f, 0.9607844f, 0.8078432f };
            light0.enabled        = true;

            // Fill light.
            light1.direction      = { 0.7198464f, 0.3420201f, 0.6040227f };
            light1.diffuse_color  = { 0.9647059f, 0.7607844f, 0.4078432f };
            light1.specular_color = Vector3::Zero;
            light1.enabled        = true;

            // Back light.
            light2.direction      = { 0.4545195f, -0.7660444f, 0.4545195f };
            light2.diffuse_color  = { 0.3231373f, 0.3607844f, 0.3937255f };
            light2.specular_color = { 0.3231373f, 0.3607844f, 0.3937255f };
            light1.enabled        = true;

            return { 0.05333332f, 0.09882354f, 0.1819608f };
        }

        EffectDirtyFlags EffectHelpers::set_world_view_proj_and_fog(const EffectDirtyFlags& dirtyFlags
                                                                  , const Matrix&           world
                                                                  , const Matrix&           view
                                                                  , const Matrix&           projection
                                                                  , Matrix&                 worldView
                                                                  , const bool&             fogEnabled
                                                                  , const float&            fogStart
                                                                  , const float&            fogEnd
                                                                  , EffectParameter&        worldViewProjParam
                                                                  , EffectParameter&        fogVectorParam)
        {
            auto result = dirtyFlags;

            // Recompute the world+view+projection matrix?
            if ((dirtyFlags & EffectDirtyFlags::WorldViewProj) != 0)
            {
                Matrix worldViewProj;

                worldView     = world * view;
                worldViewProj = worldView * projection;

                worldViewProjParam.set_value_transpose(worldViewProj);

                result &= ~EffectDirtyFlags::WorldViewProj;
            }

            if (fogEnabled)
            {
                // Recompute the fog vector?
                if ((dirtyFlags & (EffectDirtyFlags::Fog | EffectDirtyFlags::FogEnable)) != 0)
                {
                    set_fog_vector(worldView, fogStart, fogEnd, fogVectorParam);

                    result &= ~(EffectDirtyFlags::Fog | EffectDirtyFlags::FogEnable);
                }
            }
            else
            {
                // When fog is disabled, make sure the fog vector is reset to zero.
                if ((dirtyFlags & EffectDirtyFlags::FogEnable) != 0)
                {
                    fogVectorParam.set_value(Vector4::Zero);

                    result &= ~EffectDirtyFlags::FogEnable;
                }
            }

            return result;
        }

        void EffectHelpers::set_fog_vector(const Matrix&    worldView
                                         , const float&     fogStart
                                         , const float&     fogEnd
                                         , EffectParameter& fogVectorParam)
        {
            if (Math::equal(fogStart, fogEnd))
            {
                // Degenerate case: force everything to 100% fogged if start and end are the same.
                fogVectorParam.set_value(Vector4 { 0.0f, 0.0f, 0.0f, 1.0f });
            }
            else
            {
                // We want to transform vertex positions into view space, take the resulting
                // Z value, then scale and offset according to the fog start/end distances.
                // Because we only care about the Z component, the shader can do all this
                // with a float dot product, using only the Z row of the world+view matrix.

                float scale = 1.0f / (fogStart - fogEnd);

                Vector4 fogVector = { worldView.M13() * scale
                                    , worldView.M23() * scale
                                    , worldView.M33() * scale
                                    , (worldView.M43() + fogStart) * scale };

                fogVectorParam.set_value(fogVector);
            }
        }

        EffectDirtyFlags EffectHelpers::set_lighting_matrices(const EffectDirtyFlags& dirtyFlags
                                                            , const Matrix&           world
                                                            , const Matrix&           view
                                                            , EffectParameter&        worldParam
                                                            , EffectParameter&        worldInverseTransposeParam
                                                            , EffectParameter&        eyePositionParam)
        {
            auto result = dirtyFlags;

            // Set the world and world inverse transpose matrices.
            if ((dirtyFlags & EffectDirtyFlags::World) != 0)
            {
                auto worldTranspose        = Matrix::Invert(world);
                auto worldInverseTranspose = Matrix::Transpose(worldTranspose);

                worldParam.set_value_transpose(world);
                worldInverseTransposeParam.set_value_transpose(worldInverseTranspose);

                result &= ~EffectDirtyFlags::World;
            }

            // Set the eye position.
            if ((dirtyFlags & EffectDirtyFlags::EyePosition) != 0)
            {
                auto viewInverse = Matrix::Invert(view);

                eyePositionParam.set_value(viewInverse.Translation());

                result &= ~EffectDirtyFlags::EyePosition;
            }

            return result;
        }

        void EffectHelpers::set_material_color(const bool&      lightingEnabled
                                             , const float&     alpha
                                             , const Vector3&   diffuseColor
                                             , const Vector3&   emissiveColor
                                             , const Vector3&   ambientLightColor
                                             , EffectParameter& diffuseColorParam
                                             , EffectParameter& emissiveColorParam)
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
                diffuseColorParam.set_value(Vector4 { diffuseColor * alpha, alpha });
                emissiveColorParam.set_value(Vector3 { (emissiveColor + ambientLightColor * diffuseColor) * alpha });
            }
            else
            {
                diffuseColorParam.set_value(Vector4 { (diffuseColor + emissiveColor) * alpha, alpha });
            }
        }
    }
}
