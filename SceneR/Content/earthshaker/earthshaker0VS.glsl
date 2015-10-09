#version 440 core
#extension GL_ARB_shading_language_include : require
#pragma optionNV (unroll all)

layout(location = 0) in vec3 a_position;
layout(location = 2) in vec2 a_texcoord0;
layout(location = 3) in vec3 a_normal;
layout(location = 6) in vec4 a_joint;
layout(location = 7) in vec4 a_weight;

#include "/earthshaker/earthshaker0CB.glsl"

out vec3 v_light0Direction;
out vec3 v_normal;
out vec3 v_position;
out vec2 v_texcoord0;

struct VSInputNmTxWeights
{
    vec4 Position;
    vec3 Normal;
    vec4 Indices;
    vec4 Weights;
};

#define SetVSInputNmTxWeightsParams \
    vin.Position = vec4(a_position, 1.0f); \
    vin.Normal   = a_normal; \
    vin.Indices  = a_joint; \
    vin.Weights  = a_weight;

void skin(inout VSInputNmTxWeights vin, int boneCount)
{
    mat4 skinning = mat4(0.0f);

    for (int i = 0; i < boneCount; i++)
    {
        skinning += u_jointMat[int(vin.Indices[i])] * vin.Weights[i];
    }

    vin.Position = vin.Position * skinning * u_modelViewMatrix;
    vin.Normal   = vin.Normal * mat3(skinning) * mat3(u_normalMatrix);
}

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