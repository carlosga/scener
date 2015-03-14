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
in vec2 TexCoord;
in vec4 Diffuse;
in vec4 Specular;

layout (location = 0) out vec4 FragColor;

#include "/SceneR/BasicEffect.glsl"
#include "/SceneR/Structures.glsl"
#include "/SceneR/Common.glsl"
#include "/SceneR/Lighting.glsl"

// subroutine signature
subroutine vec4 PixelShader();

// Pixel shader: basic.
layout(index = 0) subroutine (PixelShader) vec4 PSBasic()
{
    PSInput pin;
    SetPSInputParams;

    vec4 color = pin.Diffuse;

    ApplyFog(color, pin.Specular.w);

    return color;
}

// Pixel shader: no fog.
layout(index = 1) subroutine (PixelShader) vec4 PSBasicNoFog()
{
    PSInputNoFog pin;
    SetPSInputNoFogParams;

    return pin.Diffuse;
}

// Pixel shader: texture.
layout(index = 2) subroutine (PixelShader) vec4 PSBasicTx()
{
    PSInputTx pin;
    SetPSInputTxParams;

    vec4 color = texture(Texture, pin.TexCoord) * pin.Diffuse;

    ApplyFog(color, pin.Specular.w);

    return color;
}

// Pixel shader: texture, no fog.
layout(index = 3) subroutine (PixelShader) vec4 PSBasicTxNoFog()
{
    PSInputTxNoFog pin;
    SetPSInputTxNoFogParams;

    return texture(Texture, pin.TexCoord) * pin.Diffuse;
}

// Pixel shader: vertex lighting.
layout(index = 4) subroutine (PixelShader) vec4 PSBasicVertexLighting()
{
    PSInput pin;
    SetPSInputParams;

    vec4 color = pin.Diffuse;

    AddSpecular(color, pin.Specular.rgb);
    ApplyFog(color, pin.Specular.w);

    return color;
}

// Pixel shader: vertex lighting, no fog.
layout(index = 5) subroutine (PixelShader) vec4 PSBasicVertexLightingNoFog()
{
    PSInput pin;
    SetPSInputParams;

    vec4 color = pin.Diffuse;

    AddSpecular(color, pin.Specular.rgb);

    return color;
}

// Pixel shader: vertex lighting + texture.
layout(index = 6) subroutine (PixelShader) vec4 PSBasicVertexLightingTx()
{
    PSInputTx pin;
    SetPSInputTxParams;

    vec4 color = texture(Texture, pin.TexCoord) * pin.Diffuse;

    AddSpecular(color, pin.Specular.rgb);
    ApplyFog(color, pin.Specular.w);

    return color;
}

// Pixel shader: vertex lighting + texture, no fog.
layout(index = 7) subroutine (PixelShader) vec4 PSBasicVertexLightingTxNoFog()
{
    PSInputTx pin;
    SetPSInputTxParams;

    vec4 color = texture(Texture, pin.TexCoord) * pin.Diffuse;

    AddSpecular(color, pin.Specular.rgb);

    return color;
}

// Pixel shader: pixel lighting.
layout(index = 8) subroutine (PixelShader) vec4 PSBasicPixelLighting()
{
    PSInputPixelLighting pin;
    SetPSInputPixelLightingParams;

    vec4 color = pin.Diffuse;

    vec3 eyeVector = normalize(EyePosition - pin.PositionWS.xyz);
    vec3 worldNormal = normalize(pin.NormalWS);

    ColorPair lightResult = ComputeLights(eyeVector, worldNormal, 3);

    color.rgb *= lightResult.Diffuse;

    AddSpecular(color, lightResult.Specular);
    ApplyFog(color, pin.PositionWS.w);

    return color;
}

// Pixel shader: pixel lighting + texture.
layout(index = 9) subroutine (PixelShader) vec4 PSBasicPixelLightingTx()
{
    PSInputPixelLightingTx pin;
    SetPSInputPixelLightingTxParams;

    vec4 color = texture(Texture, pin.TexCoord) * pin.Diffuse;

    vec3 eyeVector = normalize(EyePosition - pin.PositionWS.xyz);
    vec3 worldNormal = normalize(pin.NormalWS);

    ColorPair lightResult = ComputeLights(eyeVector, worldNormal, 3);

    color.rgb *= lightResult.Diffuse;

    AddSpecular(color, lightResult.Specular);
    ApplyFog(color, pin.PositionWS.w);

    return color;
}

// special uniform variable to control which option will be used
layout (location = 0) subroutine uniform PixelShader PixelShaderProcessor;

void main()
{
    FragColor = PixelShaderProcessor();
}
