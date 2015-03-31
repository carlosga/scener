// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
//---------------------------------------------------------------------------------------------------
// Ported from Microsoft XNA Community Game Platform Stock Effects
//---------------------------------------------------------------------------------------------------
// Microsoft XNA Community Game Platform
// Copyright (C) Microsoft Corporation. All rights reserved.
//---------------------------------------------------------------------------------------------------

float saturate(float value)
{
    return clamp(value, 0.0, 1.0);
}

float ComputeFogFactor(vec4 position)
{
    return saturate(dot(position, FogVector));
}

void ApplyFog(inout vec4 color, float fogFactor)
{
    color.rgb = mix(color.rgb, FogColor * color.a, fogFactor);
}

void AddSpecular(inout vec4 color, vec3 specular)
{
    color.rgb += specular * color.a;
}

vec4 SampleTexture(sampler2D texture, vec2 texCoord)
{
   return textureLod(texture, texCoord, textureQueryLod(texture, texCoord).t);
}

struct CommonVSOutput
{
    vec4  Pos_ps;
    vec4  Diffuse;
    vec3  Specular;
    float FogFactor;
};

CommonVSOutput ComputeCommonVSOutput(vec4 position)
{
    CommonVSOutput vout;

    vout.Pos_ps    = position * WorldViewProj;
    vout.Diffuse   = DiffuseColor;
    vout.Specular  = vec3(0.0f);
    vout.FogFactor = ComputeFogFactor(position);

    return vout;
}

//
// VS Input macros
//
#define SetVSInputParams \
    vin.Position = vec4(VertexPosition, 1.0f);

#define SetVSInputVcParams \
    vin.Position = vec4(VertexPosition, 1.0f); \
    vin.Color    = VertexColor;

#define SetVSInputTxParams \
    vin.Position = vec4(VertexPosition, 1.0f); \
    vin.TexCoord = VertexTexCoord.st;

#define SetVSInputTxVcParams \
    vin.Position = vec4(VertexPosition, 1.0f); \
    vin.TexCoord = VertexTexCoord.st; \
    vin.Color    = VertexColor;

#define SetVSInputNmParams \
    vin.Position = vec4(VertexPosition, 1.0f); \
    vin.Normal   = VertexNormal;

#define SetVSInputNmVcParams \
    vin.Position = vec4(VertexPosition, 1.0f); \
    vin.Normal   = VertexNormal; \
    vin.Color    = VertexColor;

#define SetVSInputNmTxParams \
    vin.Position = vec4(VertexPosition, 1.0f); \
    vin.Normal   = VertexNormal; \
    vin.TexCoord = VertexTexCoord.st;

#define SetVSInputNmTxVcParams \
    vin.Position = vec4(VertexPosition, 1.0f); \
    vin.Normal   = VertexNormal; \
    vin.TexCoord = VertexTexCoord.st; \
    vin.Color    = VertexColor;

//
// VS Output macros
//
#define SetCommonVSOutputParams \
    gl_Position = cout.Pos_ps; \
    Diffuse     = cout.Diffuse; \
    Specular    = vec4(cout.Specular, cout.FogFactor);

#define SetCommonVSOutputParamsNoFog \
    gl_Position = cout.Pos_ps; \
    Diffuse     = cout.Diffuse;

//
// PS Input macros
//
#define SetPSInputParams \
    pin.Diffuse  = Diffuse; \
    pin.Specular = vec4(SpecularColor, SpecularPower);

#define SetPSInputNoFogParams \
    pin.Diffuse  = Diffuse;

#define SetPSInputTxParams \
    pin.Diffuse  = Diffuse; \
    pin.Specular = vec4(SpecularColor, SpecularPower); \
    pin.TexCoord = TexCoord.st;

#define SetPSInputTxNoFogParams \
    pin.Diffuse  = Diffuse; \
    pin.TexCoord = TexCoord.st;

#define SetPSInputPixelLightingParams \
    pin.PositionWS = PositionWS; \
    pin.NormalWS   = NormalWS; \
    pin.Diffuse    = Diffuse;

#define SetPSInputPixelLightingTxParams \
    pin.TexCoord   = TexCoord; \
    pin.PositionWS = PositionWS; \
    pin.NormalWS   = NormalWS; \
    pin.Diffuse    = Diffuse;

#define SetVSInputNmTxWeightsParams \
    vin.Position = vec4(VertexPosition, 1.0f); \
    vin.Normal   = VertexNormal; \
    vin.TexCoord = VertexCoord.st; \
    vin.Indices  = BlendIndices; \
    vin.Weights  = BlendWeights;
