// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
//---------------------------------------------------------------------------------------------------
// Ported from Microsoft XNA Community Game Platform Stock Effects
//---------------------------------------------------------------------------------------------------
// Microsoft XNA Community Game Platform
// Copyright (C) Microsoft Corporation. All rights reserved.
//---------------------------------------------------------------------------------------------------

struct ColorPair
{
    vec3 Diffuse;
    vec3 Specular;
};

ColorPair ComputeLights(vec3 eyeVector, vec3 worldNormal, int numLights)
{
    mat3 lightDirections = mat3(0.0);
    mat3 lightDiffuse    = mat3(0.0);
    mat3 lightSpecular   = mat3(0.0);
    mat3 halfVectors     = mat3(0.0);

    for (int i = 0; i < numLights; i++)
    {
        lightDirections[i] = mat3(DirLight0Direction,     DirLight1Direction,     DirLight2Direction)[i];
        lightDiffuse[i]    = mat3(DirLight0DiffuseColor,  DirLight1DiffuseColor,  DirLight2DiffuseColor)[i];
        lightSpecular[i]   = mat3(DirLight0SpecularColor, DirLight1SpecularColor, DirLight2SpecularColor)[i];

        halfVectors[i]     = lightDirections[i] - eyeVector;
    }

    vec3 dotL = worldNormal * -lightDirections;
    vec3 dotH = normalize(worldNormal * -halfVectors);

    vec3 zeroL = step(0, dotL);

    vec3 diffuse  = zeroL * dotL;
    vec3 specular = pow(max(dotH, 0) * zeroL, vec3(SpecularPower));

    ColorPair result;

    result.Diffuse  = lightDiffuse * diffuse * DiffuseColor.rgb + EmissiveColor;
    result.Specular = lightSpecular * specular * SpecularColor;

    return result;
}

CommonVSOutput ComputeCommonVSOutputWithLighting(vec4 position, vec3 normal, int numLights)
{
    CommonVSOutput vout;

    vec4 pos_ws      = position * World;
    vec3 eyeVector   = normalize(EyePosition - pos_ws.xyz);
    vec3 worldNormal = normalize(normal * mat3x3(WorldInverseTranspose));

    ColorPair lightResult = ComputeLights(eyeVector, worldNormal, numLights);

    vout.Pos_ps    = position * WorldViewProj;
    vout.Diffuse   = vec4(lightResult.Diffuse, DiffuseColor.a);
    vout.Specular  = lightResult.Specular;
    vout.FogFactor = ComputeFogFactor(position);

    return vout;
}

struct CommonVSOutputPixelLighting
{
    vec4  Pos_ps;
    vec3  Pos_ws;
    vec3  Normal_ws;
    float FogFactor;
};

CommonVSOutputPixelLighting ComputeCommonVSOutputPixelLighting(vec4 position, vec3 normal)
{
    CommonVSOutputPixelLighting vout;

    vout.Pos_ps    = position * WorldViewProj;
    vout.Pos_ws    = (position * World).xyz;
    vout.Normal_ws = normalize(normal * mat3x3(WorldInverseTranspose));
    vout.FogFactor = ComputeFogFactor(position);

    return vout;
}

/*
#define SetCommonVSOutputParamsPixelLighting \
    vout.PositionPS = cout.Pos_ps; \
    vout.PositionWS = vec4(cout.Pos_ws, cout.FogFactor); \
    vout.NormalWS   = cout.Normal_ws;
*/
