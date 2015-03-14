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

layout(location = 0) in vec3 VertexPosition;
layout(location = 1) in vec4 VertexColor;
layout(location = 2) in vec3 VertexTexCoord;
layout(location = 3) in vec3 VertexNormal;

#include "/SceneR/BasicEffect.glsl"
#include "/SceneR/Structures.glsl"
#include "/SceneR/Common.glsl"
#include "/SceneR/Lighting.glsl"

out vec4 PositionWS;
out vec3 NormalWS;
out vec2 TexCoord;
out vec4 Diffuse;
out vec4 Specular;

// subroutine signature
subroutine void VertexShader();

// special uniform variable to control which option will be used
subroutine uniform VertexShader VertexShaderProcessor;

// Vertex shader: basic.
layout(index = 0) subroutine (VertexShader) void VSBasic()
{
    VSInput vin;
    SetVSInputParams;

    CommonVSOutput cout = ComputeCommonVSOutput(vin.Position);
    SetCommonVSOutputParams;
}

// Vertex shader: no fog.
layout(index = 1) subroutine (VertexShader) void VSBasicNoFog()
{
    VSInput vin;
    SetVSInputParams;

    CommonVSOutput cout = ComputeCommonVSOutput(vin.Position);
    SetCommonVSOutputParamsNoFog;
}

// Vertex shader: vertex color.
layout(index = 2) subroutine (VertexShader) void VSBasicVc()
{
    VSInputVc vin;
    SetVSInputVcParams;

    CommonVSOutput cout = ComputeCommonVSOutput(vin.Position);
    SetCommonVSOutputParams;

    Diffuse *= vin.Color;
}

// Vertex shader: vertex color, no fog.
layout(index = 3) subroutine (VertexShader) void VSBasicVcNoFog()
{
    VSInputVc vin;
    SetVSInputVcParams;

    CommonVSOutput cout = ComputeCommonVSOutput(vin.Position);
    SetCommonVSOutputParamsNoFog;

    Diffuse *= vin.Color;
}

// Vertex shader: texture.
layout(index = 4) subroutine (VertexShader) void VSBasicTx()
{
    VSInputTx vin;
    SetVSInputTxParams;

    CommonVSOutput cout = ComputeCommonVSOutput(vin.Position);
    SetCommonVSOutputParams;

    TexCoord = vin.TexCoord;
}

// Vertex shader: texture, no fog.
layout(index = 5) subroutine (VertexShader) void VSBasicTxNoFog()
{
    VSInputTx vin;
    SetVSInputTxParams;

    CommonVSOutput cout = ComputeCommonVSOutput(vin.Position);
    SetCommonVSOutputParamsNoFog;

    TexCoord = vin.TexCoord;
}

// Vertex shader: texture + vertex color.
layout(index = 6) subroutine (VertexShader) void VSBasicTxVc()
{
    VSInputTxVc vin;
    SetVSInputTxVcParams;

    CommonVSOutput cout = ComputeCommonVSOutput(vin.Position);
    SetCommonVSOutputParams;

    TexCoord = vin.TexCoord;
    Diffuse *= vin.Color;
}

// Vertex shader: texture + vertex color, no fog.
layout(index = 7) subroutine (VertexShader) void VSBasicTxVcNoFog()
{
    VSInputTxVc vin;
    SetVSInputTxVcParams;

    CommonVSOutput cout = ComputeCommonVSOutput(vin.Position);
    SetCommonVSOutputParamsNoFog;

    TexCoord = vin.TexCoord;
    Diffuse *= vin.Color;
}

// Vertex shader: vertex lighting.
layout(index = 8) subroutine (VertexShader) void VSBasicVertexLighting()
{
    VSInputNm vin;
    SetVSInputNmParams;

    CommonVSOutput cout = ComputeCommonVSOutputWithLighting(vin.Position, vin.Normal, 3);
    SetCommonVSOutputParams;
}

// Vertex shader: vertex lighting + vertex color.
layout(index = 9) subroutine (VertexShader) void VSBasicVertexLightingVc()
{
    VSInputNmVc vin;
    SetVSInputNmVcParams;

    CommonVSOutput cout = ComputeCommonVSOutputWithLighting(vin.Position, vin.Normal, 3);
    SetCommonVSOutputParams;
}

// Vertex shader: vertex lighting + texture.
layout(index = 10) subroutine (VertexShader) void VSBasicVertexLightingTx()
{
    VSInputNmTx vin;
    SetVSInputNmTxParams;

    CommonVSOutput cout = ComputeCommonVSOutputWithLighting(vin.Position, vin.Normal, 3);
    SetCommonVSOutputParams;

    TexCoord = vin.TexCoord;
}

// Vertex shader: vertex lighting + texture + vertex color.
layout(index = 11) subroutine (VertexShader) void VSBasicVertexLightingTxVc()
{
    VSInputNmTxVc vin;
    SetVSInputNmTxVcParams;

    CommonVSOutput cout = ComputeCommonVSOutputWithLighting(vin.Position, vin.Normal, 3);
    SetCommonVSOutputParams;

    TexCoord = vin.TexCoord;
    Diffuse *= vin.Color;
}

// Vertex shader: one light.
layout(index = 12) subroutine (VertexShader) void VSBasicOneLight()
{
    VSInputNm vin;
    SetVSInputNmParams;

    CommonVSOutput cout = ComputeCommonVSOutputWithLighting(vin.Position, vin.Normal, 1);
    SetCommonVSOutputParams;
}

// Vertex shader: one light + vertex color.
layout(index = 13) subroutine (VertexShader) void VSBasicOneLightVc()
{
    VSInputNmVc vin;
    SetVSInputNmVcParams;

    CommonVSOutput cout = ComputeCommonVSOutputWithLighting(vin.Position, vin.Normal, 1);
    SetCommonVSOutputParams;

    Diffuse *= vin.Color;
}

// Vertex shader: one light + texture.
layout(index = 14) subroutine (VertexShader) void VSBasicOneLightTx()
{
    VSInputNmTx vin;
    SetVSInputNmTxParams;

    CommonVSOutput cout = ComputeCommonVSOutputWithLighting(vin.Position, vin.Normal, 1);
    SetCommonVSOutputParams;

    TexCoord = vin.TexCoord;
}

// Vertex shader: one light + texture + vertex color.
layout(index = 15) subroutine (VertexShader) void VSBasicOneLightTxVc()
{
    VSInputNmTxVc vin;
    SetVSInputNmTxVcParams;

    CommonVSOutput cout = ComputeCommonVSOutputWithLighting(vin.Position, vin.Normal, 1);
    SetCommonVSOutputParams;

    TexCoord = vin.TexCoord;
    Diffuse *= vin.Color;
}

// Vertex shader: pixel lighting.
layout(index = 16) subroutine (VertexShader) void VSBasicPixelLighting()
{
    VSInputNm vin;
    SetVSInputNmParams;

    CommonVSOutputPixelLighting cout = ComputeCommonVSOutputPixelLighting(vin.Position, vin.Normal);
    SetCommonVSOutputParamsPixelLighting;

    Diffuse = vec4(1.0f, 1.0f, 1.0f, DiffuseColor.a);
}

// Vertex shader: pixel lighting + vertex color.
layout(index = 17) subroutine (VertexShader) void VSBasicPixelLightingVc()
{
    VSInputNmVc vin;
    SetVSInputNmVcParams;

    CommonVSOutputPixelLighting cout = ComputeCommonVSOutputPixelLighting(vin.Position, vin.Normal);
    SetCommonVSOutputParamsPixelLighting;

    Diffuse.rgb = vin.Color.rgb;
    Diffuse.a   = vin.Color.a * DiffuseColor.a;
}

// Vertex shader: pixel lighting + texture.
layout(index = 18) subroutine (VertexShader) void VSBasicPixelLightingTx()
{
    VSInputNmTx vin;
    SetVSInputNmTxParams;

    CommonVSOutputPixelLighting cout = ComputeCommonVSOutputPixelLighting(vin.Position, vin.Normal);
    SetCommonVSOutputParamsPixelLighting;

    Diffuse  = vec4(1, 1, 1, DiffuseColor.a);
    TexCoord = vin.TexCoord;
}

// Vertex shader: pixel lighting + texture + vertex color.
layout(index = 19) subroutine (VertexShader) void VSBasicPixelLightingTxVc()
{
    VSInputNmTxVc vin;
    SetVSInputNmTxVcParams;

    CommonVSOutputPixelLighting cout = ComputeCommonVSOutputPixelLighting(vin.Position, vin.Normal);
    SetCommonVSOutputParamsPixelLighting;

    Diffuse.rgb = vin.Color.rgb;
    Diffuse.a   = vin.Color.a * DiffuseColor.a;
    TexCoord    = vin.TexCoord;
}

void main()
{
    // VertexShaderProcessor();

    CommonVSOutputPixelLighting cout = ComputeCommonVSOutputPixelLighting(vec4(VertexPosition, 1.0f), VertexNormal);

    gl_Position = cout.Pos_ps;
    PositionWS  = vec4(cout.Pos_ws, cout.FogFactor);
    NormalWS    = cout.Normal_ws;
    TexCoord    = VertexTexCoord.st;
    Diffuse     = vec4(1.0, 1.0, 1.0, DiffuseColor.a);
}
