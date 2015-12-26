#version 430 core

layout(location = 0) in vec3 a_position;
layout(location = 2) in vec2 a_texcoord0;
layout(location = 3) in vec3 a_normal;
layout(location = 6) in vec4 a_joint;
layout(location = 7) in vec4 a_weight;

#include "earthshaker0CB.glsl"
#include "structures.glsl"
#include "common.glsl"
#include "skinning.glsl"

out vec3 v_normal;
out vec2 v_texcoord0;
out vec3 v_light0Direction;
out vec3 v_position;

void main(void)
{
    VSInputNmTxWeights vin;
    SetVSInputNmTxWeightsParams;

    skin(vin, 4);

    v_normal    	  = vin.Normal;
    v_texcoord0 	  = a_texcoord0;
    v_position 		  = vin.Position.xyz;
    v_light0Direction = u_light0Transform[3].xyz - vin.Position.xyz;
    gl_Position 	  = u_projectionMatrix * vin.Position;
}
