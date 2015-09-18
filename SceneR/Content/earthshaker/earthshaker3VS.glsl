#version 440 core
#extension GL_ARB_shading_language_include : require
#pragma optionNV (unroll all)

layout(location = 0) in vec3 a_position;
layout(location = 2) in vec2 a_texcoord0;
layout(location = 3) in vec3 a_normal;
layout(location = 6) in vec4 a_joint;
layout(location = 7) in vec4 a_weight;

#include "/earthshaker/earthshaker3CB.glsl"

out vec3 v_light0Direction;
out vec3 v_normal;
out vec3 v_position;
out vec2 v_texcoord0;

void main(void)
{
//    mat4 skinMat = a_weight.x * u_jointMat[int(a_joint.x)];
//    skinMat += a_weight.y * u_jointMat[int(a_joint.y)];
//    skinMat += a_weight.z * u_jointMat[int(a_joint.z)];
//    skinMat += a_weight.w * u_jointMat[int(a_joint.w)];

//    vec4 pos = u_modelViewMatrix * skinMat * vec4(a_position,1.0);
//    v_normal          = u_normalMatrix * mat3(skinMat)* a_normal;
//    v_texcoord0       = a_texcoord0;
//    v_light0Direction = u_light0Transform[3].xyz - pos.xyz;
//    gl_Position       = u_projectionMatrix * pos;

    //vec3  Pos_ws = (a_position * u_modelViewMatrix).xyz;
    vec4 pos_ps = vec4(a_position, 1.0) * u_projectionMatrix;

    v_light0Direction = u_light0Transform[3].xyz - pos_ps.xyz;
    v_normal          = normalize(a_normal * mat3x3(u_normalMatrix));
    v_texcoord0       = a_texcoord0;
    gl_Position       = pos_ps;
}
