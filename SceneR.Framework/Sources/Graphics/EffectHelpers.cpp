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

using namespace System;
using namespace SceneR::Framework;
using namespace SceneR::Graphics;


Vector3 EffectHelpers::EnableDefaultLighting(DirectionalLight& light0
                                           , DirectionalLight& light1
                                           , DirectionalLight& light2)
{
    // Key light.
    light0.Direction({ -0.5265408f, -0.5735765f, -0.6275069f });
    light0.DiffuseColor({ 1.0f, 0.9607844f, 0.8078432f });
    light0.SpecularColor({ 1.0f, 0.9607844f, 0.8078432f });
    light0.Enabled(true);

    // Fill light.
    light1.Direction({ 0.7198464f, 0.3420201f, 0.6040227f });
    light1.DiffuseColor({ 0.9647059f, 0.7607844f, 0.4078432f });
    light1.SpecularColor(Vector3::Zero);
    light1.Enabled(true);

    // Back light.
    light2.Direction({ 0.4545195f, -0.7660444f, 0.4545195f });
    light2.DiffuseColor({ 0.3231373f, 0.3607844f, 0.3937255f });
    light2.SpecularColor({ 0.3231373f, 0.3607844f, 0.3937255f });
    light2.Enabled(true);

    return { 0.05333332f, 0.09882354f, 0.1819608f };
}

EffectDirtyFlags EffectHelpers::SetWorldViewProjAndFog(const EffectDirtyFlags& dirtyFlags
                                                     , const Matrix&           world
                                                     , const Matrix&           view
                                                     , const Matrix&           projection
                                                     , Matrix&                 worldView
                                                     , const Boolean&          fogEnabled
                                                     , const Single&           fogStart
                                                     , const Single&           fogEnd
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

        worldViewProjParam.SetValueTranspose(worldViewProj);

        result &= ~EffectDirtyFlags::WorldViewProj;
    }

    if (fogEnabled)
    {
        // Recompute the fog vector?
        if ((dirtyFlags & (EffectDirtyFlags::Fog | EffectDirtyFlags::FogEnable)) != 0)
        {
            SetFogVector(worldView, fogStart, fogEnd, fogVectorParam);

            result &= ~(EffectDirtyFlags::Fog | EffectDirtyFlags::FogEnable);
        }
    }
    else
    {
        // When fog is disabled, make sure the fog vector is reset to zero.
        if ((dirtyFlags & EffectDirtyFlags::FogEnable) != 0)
        {
            fogVectorParam.SetValue(Vector4::Zero);

            result &= ~EffectDirtyFlags::FogEnable;
        }
    }

    return result;
}

void EffectHelpers::SetFogVector(const Matrix&    worldView
                               , const Single&    fogStart
                               , const Single&    fogEnd
                               , EffectParameter& fogVectorParam)
{
    if (fogStart == fogEnd)
    {
        // Degenerate case: force everything to 100% fogged if start and end are the same.
        fogVectorParam.SetValue(Vector4 { 0.0f, 0.0f, 0.0f, 1.0f });
    }
    else
    {
        // We want to transform vertex positions into view space, take the resulting
        // Z value, then scale and offset according to the fog start/end distances.
        // Because we only care about the Z component, the shader can do all this
        // with a single dot product, using only the Z row of the world+view matrix.

        Single scale = 1.0f / (fogStart - fogEnd);

        Vector4 fogVector = { worldView.M13() * scale
                            , worldView.M23() * scale
                            , worldView.M33() * scale
                            , (worldView.M43() + fogStart) * scale };

        fogVectorParam.SetValue(fogVector);
    }
}

EffectDirtyFlags EffectHelpers::SetLightingMatrices(const EffectDirtyFlags& dirtyFlags
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

        worldParam.SetValueTranspose(world);
        worldInverseTransposeParam.SetValueTranspose(worldInverseTranspose);

        result &= ~EffectDirtyFlags::World;
    }

    // Set the eye position.
    if ((dirtyFlags & EffectDirtyFlags::EyePosition) != 0)
    {
        auto viewInverse = Matrix::Invert(view);

        eyePositionParam.SetValue(viewInverse.Translation());

        result &= ~EffectDirtyFlags::EyePosition;
    }

    return result;
}

void EffectHelpers::SetMaterialColor(const Boolean&   lightingEnabled
                                   , const Single&    alpha
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
        diffuseColorParam.SetValue(Vector4 { diffuseColor * alpha, alpha });
        emissiveColorParam.SetValue(Vector3 { (emissiveColor + ambientLightColor * diffuseColor) * alpha });
    }
    else
    {
        diffuseColorParam.SetValue(Vector4 { (diffuseColor + emissiveColor) * alpha, alpha });
    }
}
