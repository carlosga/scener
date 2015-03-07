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

uniform sampler2D Texture;

#include "/SceneR/BasicEffect.glsl"
#include "/SceneR/Structures.glsl"
#include "/SceneR/Common.glsl"
#include "/SceneR/Lighting.glsl"

void main()
{
    vec4      color       = texture(Texture, TexCoord.st) * Diffuse;
    vec3      eyeVector   = normalize(EyePosition - PositionWS.xyz);
    vec3      worldNormal = normalize(NormalWS);
    ColorPair lightResult = ComputeLights(eyeVector, worldNormal, 3);

    color.rgb *= lightResult.Diffuse;

    AddSpecular(color, lightResult.Specular);
    ApplyFog(color, PositionWS.w);

    FragColor = color;
}
