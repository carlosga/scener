// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
//---------------------------------------------------------------------------------------------------
// Ported from Microsoft XNA Community Game Platform Stock Effects
//---------------------------------------------------------------------------------------------------
// Microsoft XNA Community Game Platform
// Copyright (C) Microsoft Corporation. All rights reserved.
//---------------------------------------------------------------------------------------------------

#version 440 core
#extension GL_ARB_shading_language_include : require
#pragma optionNV (unroll all)

layout (location = 0) in vec3  VertexPosition;
layout (location = 2) in vec3  VertexCoord;
layout (location = 3) in vec3  VertexNormal;
layout (location = 6) in ivec4 BlendIndices;
layout (location = 7) in vec4  BlendWeights;

#include "/SceneR/SkinnedEffect.glsl"
#include "/SceneR/Structures.glsl"
#include "/SceneR/Common.glsl"
#include "/SceneR/Lighting.glsl"

out vec4 PositionWS;
out vec3 NormalWS;
out vec2 TexCoord;
out vec4 Diffuse;
out vec4 Specular;

void Skin(inout VSInputNmTxWeights vin, uint boneCount)
{
    mat4 skinning = mat4(0.0f);

    for (int i = 0; i < boneCount; i++)
    {
        skinning += Bones[vin.Indices[i]] * vin.Weights[i];
    }

    vin.Position.xyz = vec3(skinning * vin.Position);
    vin.Normal       = vin.Normal * mat3x3(skinning);
}

// subroutine signature
subroutine void VertexShader();

// Vertex shader: vertex lighting, one bone.
layout(index = 0) subroutine (VertexShader) void VSSkinnedVertexLightingOneBone()
{
    VSInputNmTxWeights vin;
    SetVSInputNmTxWeightsParams;

    Skin(vin, 1);

    CommonVSOutput cout = ComputeCommonVSOutputWithLighting(vin.Position, vin.Normal, 3);
    SetCommonVSOutputParams;

    TexCoord = vin.TexCoord;
}

// Vertex shader: vertex lighting, two bones.
layout(index = 1) subroutine (VertexShader) void VSSkinnedVertexLightingTwoBones()
{
    VSInputNmTxWeights vin;
    SetVSInputNmTxWeightsParams;

    Skin(vin, 2);

    CommonVSOutput cout = ComputeCommonVSOutputWithLighting(vin.Position, vin.Normal, 3);
    SetCommonVSOutputParams;

    TexCoord = vin.TexCoord;
}

// Vertex shader: vertex lighting, four bones.
layout(index = 2) subroutine (VertexShader) void VSSkinnedVertexLightingFourBones()
{
    VSInputNmTxWeights vin;
    SetVSInputNmTxWeightsParams;

    Skin(vin, 4);

    CommonVSOutput cout = ComputeCommonVSOutputWithLighting(vin.Position, vin.Normal, 3);
    SetCommonVSOutputParams;

    TexCoord = vin.TexCoord;
}

// Vertex shader: one light, one bone.
layout(index = 3) subroutine (VertexShader) void VSSkinnedOneLightOneBone()
{
    VSInputNmTxWeights vin;
    SetVSInputNmTxWeightsParams;

    Skin(vin, 1);

    CommonVSOutput cout = ComputeCommonVSOutputWithLighting(vin.Position, vin.Normal, 1);
    SetCommonVSOutputParams;

    TexCoord = vin.TexCoord;
}

// Vertex shader: one light, two bones.
layout(index = 4) subroutine (VertexShader) void VSSkinnedOneLightTwoBones()
{
    VSInputNmTxWeights vin;
    SetVSInputNmTxWeightsParams;

    Skin(vin, 2);

    CommonVSOutput cout = ComputeCommonVSOutputWithLighting(vin.Position, vin.Normal, 1);
    SetCommonVSOutputParams;

    TexCoord = vin.TexCoord;
}

// Vertex shader: one light, four bones.
layout(index = 5) subroutine (VertexShader) void VSSkinnedOneLightFourBones()
{
    VSInputNmTxWeights vin;
    SetVSInputNmTxWeightsParams;

    Skin(vin, 4);

    CommonVSOutput cout = ComputeCommonVSOutputWithLighting(vin.Position, vin.Normal, 1);
    SetCommonVSOutputParams;

    TexCoord = vin.TexCoord;
}

// Vertex shader: pixel lighting, one bone.
layout(index = 6) subroutine (VertexShader) void VSSkinnedPixelLightingOneBone()
{
    VSInputNmTxWeights vin;
    SetVSInputNmTxWeightsParams;

    Skin(vin, 1);

    CommonVSOutputPixelLighting cout = ComputeCommonVSOutputPixelLighting(vin.Position, vin.Normal);
    SetCommonVSOutputParamsPixelLighting;

    Diffuse  = vec4(1.0f, 1.0f, 1.0f, DiffuseColor.a);
    TexCoord = vin.TexCoord;
}

// Vertex shader: pixel lighting, two bones.
layout(index = 7) subroutine (VertexShader) void VSSkinnedPixelLightingTwoBones()
{
    VSInputNmTxWeights vin;
    SetVSInputNmTxWeightsParams;

    Skin(vin, 2);

    CommonVSOutputPixelLighting cout = ComputeCommonVSOutputPixelLighting(vin.Position, vin.Normal);
    SetCommonVSOutputParamsPixelLighting;

    Diffuse  = vec4(1.0f, 1.0f, 1.0f, DiffuseColor.a);
    TexCoord = vin.TexCoord;
}

// Vertex shader: pixel lighting, four bones.
layout(index = 8) subroutine (VertexShader) void VSSkinnedPixelLightingFourBones()
{
    VSInputNmTxWeights vin;
    SetVSInputNmTxWeightsParams;

    Skin(vin, 4);

    CommonVSOutputPixelLighting cout = ComputeCommonVSOutputPixelLighting(vin.Position, vin.Normal);
    SetCommonVSOutputParamsPixelLighting;

    Diffuse  = vec4(1.0f, 1.0f, 1.0f, DiffuseColor.a);
    TexCoord = vin.TexCoord;
}

// special uniform variable to control which option will be used
layout (location = 0) subroutine uniform VertexShader VertexShaderProcessor;

void main()
{
    VertexShaderProcessor();
}
