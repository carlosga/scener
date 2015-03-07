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

out vec4 PositionWS;
out vec3 NormalWS;
out vec3 TexCoord;
out vec4 Diffuse;

#include "/SceneR/BasicEffect.glsl"
#include "/SceneR/Structures.glsl"
#include "/SceneR/Common.glsl"
#include "/SceneR/Lighting.glsl"

void main()
{
    CommonVSOutputPixelLighting cout = ComputeCommonVSOutputPixelLighting(vec4(VertexPosition, 1.0f), VertexNormal);

    gl_Position = cout.Pos_ps;
    PositionWS  = vec4(cout.Pos_ws, cout.FogFactor);
    NormalWS    = cout.Normal_ws;
    TexCoord    = VertexCoord;
    Diffuse     = vec4(1.0, 1.0, 1.0, DiffuseColor.a);
}
