// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
//---------------------------------------------------------------------------------------------------
// Ported from Microsoft XNA Community Game Platform Stock Effects
//---------------------------------------------------------------------------------------------------
// Microsoft XNA Community Game Platform
// Copyright (C) Microsoft Corporation. All rights reserved.
//---------------------------------------------------------------------------------------------------

//
// Vertex shader input structures.
//

struct VSInput
{
    vec4 Position;
};

struct VSInputVc
{
    vec4 Position;
    vec4 Color;
};

struct VSInputTx
{
    vec4 Position;
    vec2 TexCoord;
};

struct VSInputTxVc
{
    vec4 Position;
    vec2 TexCoord;
    vec4 Color;
};

struct VSInputNm
{
    vec4 Position;
    vec3 Normal;
};

struct VSInputNmVc
{
    vec4 Position;
    vec3 Normal;
    vec4 Color;
};

struct VSInputNmTx
{
    vec4 Position;
    vec3 Normal;
    vec2 TexCoord;
};

struct VSInputNmTxVc
{
    vec4 Position;
    vec3 Normal;
    vec2 TexCoord;
    vec4 Color;
};

struct VSInputTx2
{
    vec4 Position;
    vec2 TexCoord;
    vec2 TexCoord2;
};

struct VSInputTx2Vc
{
    vec4 Position;
    vec2 TexCoord;
    vec2 TexCoord2;
    vec4 Color;
};

struct VSInputNmTxWeights
{
    vec4  Position;
    vec3  Normal;
    vec2  TexCoord;
    ivec4 Indices;
    vec4  Weights;
};

//
// Vertex shader output structures.
//

struct VSOutput
{
    vec4 Diffuse;
    vec4 Specular;
    vec4 PositionPS;
};

struct VSOutputNoFog
{
    vec4 Diffuse;
    vec4 PositionPS;
};

struct VSOutputTx
{
    vec4 Diffuse;
    vec4 Specular;
    vec2 TexCoord;
    vec4 PositionPS;
};

struct VSOutputTxNoFog
{
    vec4 Diffuse;
    vec2 TexCoord;
    vec4 PositionPS;
};

struct VSOutputPixelLighting
{
    vec4 PositionWS;
    vec3 NormalWS;
    vec4 Diffuse;
    vec4 PositionPS;
};

struct VSOutputPixelLightingTx
{
    vec2 TexCoord;
    vec4 PositionWS;
    vec3 NormalWS;
    vec4 Diffuse;
    vec4 PositionPS;
};

struct VSOutputTx2
{
    vec4 Diffuse;
    vec4 Specular;
    vec2 TexCoord;
    vec2 TexCoord2;
    vec4 PositionPS;
};

struct VSOutputTx2NoFog
{
    vec4 Diffuse;
    vec2 TexCoord;
    vec2 TexCoord2;
    vec4 PositionPS;
};

struct VSOutputTxEnvMap
{
    vec4 Diffuse;
    vec4 Specular;
    vec2 TexCoord;
    vec3 EnvCoord;
    vec4 PositionPS;
};

//
// Pixel shader input structures.
//

struct PSInput
{
    vec4 Diffuse;
    vec4 Specular;
};

struct PSInputNoFog
{
    vec4 Diffuse;
};

struct PSInputTx
{
    vec4 Diffuse;
    vec4 Specular;
    vec2 TexCoord;
};

struct PSInputTxNoFog
{
    vec4 Diffuse;
    vec2 TexCoord;
};

struct PSInputPixelLighting
{
    vec4 PositionWS;
    vec3 NormalWS;
    vec4 Diffuse;
};

struct PSInputPixelLightingTx
{
    vec2 TexCoord;
    vec4 PositionWS;
    vec3 NormalWS;
    vec4 Diffuse;
};

struct PSInputTx2
{
    vec4 Diffuse;
    vec4 Specular;
    vec2 TexCoord;
    vec2 TexCoord2;
};

struct PSInputTx2NoFog
{
    vec4 Diffuse;
    vec2 TexCoord;
    vec2 TexCoord2;
};

struct PSInputTxEnvMap
{
    vec4 Diffuse;
    vec4 Specular;
    vec2 TexCoord;
    vec3 EnvCoord;
};
