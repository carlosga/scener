#version 440 core
#extension GL_ARB_shading_language_include : require
#pragma optionNV (unroll all)

layout(location = 0) in vec3 a_position;
layout(location = 2) in vec2 a_texcoord0;
layout(location = 3) in vec3 a_normal;
layout(location = 6) in vec4 a_joint;
layout(location = 7) in vec4 a_weight;

#include "/earthshaker/earthshaker0CB.glsl"
#include "/earthshaker/structures.glsl"
#include "/earthshaker/common.glsl"
#include "/earthshaker/skinning.glsl"

out vec3 v_light0Direction;
out vec3 v_normal;
out vec3 v_position;
out vec2 v_texcoord0;

void main(void)
{
    VSInputNmTxWeights vin;
    SetVSInputNmTxWeightsParams;

    skin(vin, 4);

    v_normal          = vin.Normal;
    v_light0Direction = u_light0Transform[3].xyz - vin.Position.xyz;
    v_texcoord0       = a_texcoord0;
    v_position        = vin.Position.xyz;
    gl_Position       = vin.Position * u_projectionMatrix;
}