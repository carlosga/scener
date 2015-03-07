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

/*
#define SetCommonVSOutputParams \
    vout.PositionPS = cout.Pos_ps; \
    vout.Diffuse    = cout.Diffuse; \
    vout.Specular   = float4(cout.Specular, cout.FogFactor);

#define SetCommonVSOutputParamsNoFog \
    vout.PositionPS = cout.Pos_ps; \
    vout.Diffuse    = cout.Diffuse;
*/
