// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
//---------------------------------------------------------------------------------------------------
// Ported from Microsoft XNA Community Game Platform Stock Effects
//---------------------------------------------------------------------------------------------------
// Microsoft XNA Community Game Platform
// Copyright (C) Microsoft Corporation. All rights reserved.
//---------------------------------------------------------------------------------------------------

//layout (std140, row_major) uniform Parameters   // cbuffer Parameters : register(b0)
//{
uniform vec4  DiffuseColor;             // _vs(c0)  _ps(c1)  _cb(c0);
uniform vec3  EmissiveColor;            // _vs(c1)  _ps(c2)  _cb(c1);
uniform vec3  SpecularColor;            // _vs(c2)  _ps(c3)  _cb(c2);
uniform float SpecularPower;            // _vs(c3)  _ps(c4)  _cb(c2.w);

uniform vec3  DirLight0Direction;       // _vs(c4)  _ps(c5)  _cb(c3);
uniform vec3  DirLight0DiffuseColor;    // _vs(c5)  _ps(c6)  _cb(c4);
uniform vec3  DirLight0SpecularColor;   // _vs(c6)  _ps(c7)  _cb(c5);

uniform vec3  DirLight1Direction;       // _vs(c7)  _ps(c8)  _cb(c6);
uniform vec3  DirLight1DiffuseColor;    // _vs(c8)  _ps(c9)  _cb(c7);
uniform vec3  DirLight1SpecularColor;   // _vs(c9)  _ps(c10) _cb(c8);

uniform vec3  DirLight2Direction;       // _vs(c10) _ps(c11) _cb(c9);
uniform vec3  DirLight2DiffuseColor;    // _vs(c11) _ps(c12) _cb(c10);
uniform vec3  DirLight2SpecularColor;   // _vs(c12) _ps(c13) _cb(c11);

uniform vec3  EyePosition;              // _vs(c13) _ps(c14) _cb(c12);

uniform vec3  FogColor;                 //          _ps(c0)  _cb(c13);
uniform vec4  FogVector;                // _vs(c14)          _cb(c14);

uniform int   ShaderIndex;

uniform mat4  World;
uniform mat4  WorldInverseTranspose;
uniform mat4  WorldViewProj;
//};

