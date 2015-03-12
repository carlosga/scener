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

in vec4 PositionWS;
in vec3 NormalWS;
in vec3 TexCoord;
in vec4 Diffuse;

layout (location = 0) out vec4 FragColor;

#include "/SceneR/BasicEffect.glsl"
#include "/SceneR/Structures.glsl"
#include "/SceneR/Common.glsl"
#include "/SceneR/Lighting.glsl"

// subroutine signature
subroutine vec4 PixelShader();

// special uniform variable to control which option will be used
layout(location = 20) subroutine uniform PixelShader PixelShaderProcessor;

// Pixel shader: basic.
layout(index = 0) subroutine (VertexShader) vec4 PSBasic()
{
    PSInput pin;
    vec4 color = pin.Diffuse;

    ApplyFog(color, pin.Specular.w);

    return color;
}

/*
// Pixel shader: no fog.
float4 PSBasicNoFog(PSInputNoFog pin) : SV_Target0
{
    return pin.Diffuse;
}


// Pixel shader: texture.
float4 PSBasicTx(PSInputTx pin) : SV_Target0
{
    float4 color = SAMPLE_TEXTURE(Texture, pin.TexCoord) * pin.Diffuse;

    ApplyFog(color, pin.Specular.w);

    return color;
}


// Pixel shader: texture, no fog.
float4 PSBasicTxNoFog(PSInputTxNoFog pin) : SV_Target0
{
    return SAMPLE_TEXTURE(Texture, pin.TexCoord) * pin.Diffuse;
}


// Pixel shader: vertex lighting.
float4 PSBasicVertexLighting(PSInput pin) : SV_Target0
{
    float4 color = pin.Diffuse;

    AddSpecular(color, pin.Specular.rgb);
    ApplyFog(color, pin.Specular.w);

    return color;
}


// Pixel shader: vertex lighting, no fog.
float4 PSBasicVertexLightingNoFog(PSInput pin) : SV_Target0
{
    float4 color = pin.Diffuse;

    AddSpecular(color, pin.Specular.rgb);

    return color;
}


// Pixel shader: vertex lighting + texture.
float4 PSBasicVertexLightingTx(PSInputTx pin) : SV_Target0
{
    float4 color = SAMPLE_TEXTURE(Texture, pin.TexCoord) * pin.Diffuse;

    AddSpecular(color, pin.Specular.rgb);
    ApplyFog(color, pin.Specular.w);

    return color;
}


// Pixel shader: vertex lighting + texture, no fog.
float4 PSBasicVertexLightingTxNoFog(PSInputTx pin) : SV_Target0
{
    float4 color = SAMPLE_TEXTURE(Texture, pin.TexCoord) * pin.Diffuse;

    AddSpecular(color, pin.Specular.rgb);

    return color;
}


// Pixel shader: pixel lighting.
float4 PSBasicPixelLighting(PSInputPixelLighting pin) : SV_Target0
{
    float4 color = pin.Diffuse;

    float3 eyeVector = normalize(EyePosition - pin.PositionWS.xyz);
    float3 worldNormal = normalize(pin.NormalWS);

    ColorPair lightResult = ComputeLights(eyeVector, worldNormal, 3);

    color.rgb *= lightResult.Diffuse;

    AddSpecular(color, lightResult.Specular);
    ApplyFog(color, pin.PositionWS.w);

    return color;
}


// Pixel shader: pixel lighting + texture.
float4 PSBasicPixelLightingTx(PSInputPixelLightingTx pin) : SV_Target0
{
    float4 color = SAMPLE_TEXTURE(Texture, pin.TexCoord) * pin.Diffuse;

    float3 eyeVector = normalize(EyePosition - pin.PositionWS.xyz);
    float3 worldNormal = normalize(pin.NormalWS);

    ColorPair lightResult = ComputeLights(eyeVector, worldNormal, 3);

    color.rgb *= lightResult.Diffuse;

    AddSpecular(color, lightResult.Specular);
    ApplyFog(color, pin.PositionWS.w);

    return color;
}
*/

void main()
{
    FragColor = PixelShaderProcessor();

    /*
    vec4      color       = texture(Texture, TexCoord.st) * Diffuse;
    vec3      eyeVector   = normalize(EyePosition - PositionWS.xyz);
    vec3      worldNormal = normalize(NormalWS);
    ColorPair lightResult = ComputeLights(eyeVector, worldNormal, 3);

    color.rgb *= lightResult.Diffuse;

    AddSpecular(color, lightResult.Specular);
    ApplyFog(color, PositionWS.w);

    FragColor = color;
    */
}
