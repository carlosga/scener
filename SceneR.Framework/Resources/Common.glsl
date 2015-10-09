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
    vin.Position = vec4(a_position, 1.0f);

#define SetVSInputVcParams \
    vin.Position = vec4(a_position, 1.0f); \
    vin.Color    = a_color;

#define SetVSInputTxParams \
    vin.Position = vec4(a_position, 1.0f); \
    vin.TexCoord = a_texcoord0.st;

#define SetVSInputTxVcParams \
    vin.Position = vec4(a_position, 1.0f); \
    vin.TexCoord = a_texcoord0.st; \
    vin.Color    = a_color;

#define SetVSInputNmParams \
    vin.Position = vec4(a_position, 1.0f); \
    vin.Normal   = a_normal;

#define SetVSInputNmVcParams \
    vin.Position = vec4(a_position, 1.0f); \
    vin.Normal   = a_normal; \
    vin.Color    = a_color;

#define SetVSInputNmTxParams \
    vin.Position = vec4(a_position, 1.0f); \
    vin.Normal   = a_normal; \
    vin.TexCoord = a_texcoord0.st;

#define SetVSInputNmTxVcParams \
    vin.Position = vec4(a_position, 1.0f); \
    vin.Normal   = a_normal; \
    vin.TexCoord = a_texcoord0.st; \
    vin.Color    = a_color;

//
// VS Output macros
//
#define SetCommonVSOutputParams \
    gl_Position = cout.Pos_ps; \
    Diffuse     = cout.Diffuse; \
    v_specular  = vec4(cout.Specular, cout.FogFactor);

#define SetCommonVSOutputParamsNoFog \
    gl_Position = cout.Pos_ps; \
    v_diffuse   = cout.Diffuse;

//
// PS Input macros
//
#define SetPSInputParams \
    pin.Diffuse  = v_diffuse; \
    pin.Specular = vec4(u_specular_color, u_specular_power);

#define SetPSInputNoFogParams \
    pin.Diffuse  = v_diffuse;

#define SetPSInputTxParams \
    pin.Diffuse  = v_diffuse; \
    pin.Specular = vec4(u_specular_color, u_specular_power); \
    pin.TexCoord = v_texcoord0.st;

#define SetPSInputTxNoFogParams \
    pin.Diffuse  = v_diffuse; \
    pin.TexCoord = v_texcoord0.st;

#define SetPSInputPixelLightingParams \
    pin.PositionWS = v_position; \
    pin.NormalWS   = v_normal; \
    pin.Diffuse    = v_diffuse;

#define SetPSInputPixelLightingTxParams \
    pin.TexCoord   = v_texcoord0; \
    pin.PositionWS = v_position; \
    pin.NormalWS   = v_normal; \
    pin.Diffuse    = v_diffuse;

#define SetVSInputNmTxWeightsParams \
    vin.Position = vec4(a_position, 1.0f); \
    vin.Normal   = a_normal; \
    vin.TexCoord = a_texcoord0.st; \
    vin.Indices  = a_joint; \
    vin.Weights  = a_weight;
