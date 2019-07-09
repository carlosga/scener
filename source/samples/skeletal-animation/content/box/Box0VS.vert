#version 450 core

#extension GL_GOOGLE_include_directive : require
#extension GL_ARB_separate_shader_objects : enable

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_normal;

#include "Box0CB.glsl"
#include "structures.glsl"
#include "common.glsl"

out vec3 v_normal;

void main(void)
{
    VSInput vin;
    SetVSInputParams;

    vec4 pos    = u_modelViewMatrix * vin.Position;
    v_normal    = (u_normalMatrix * vec4(a_normal, 1)).xyz;
    gl_Position = u_projectionMatrix * pos;
}
