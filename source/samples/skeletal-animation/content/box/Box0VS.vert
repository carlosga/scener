#version 450 core

#extension GL_GOOGLE_include_directive : require
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 a_position;
layout(location = 3) in vec3 a_normal;

#include "Box0CB.glsl"
#include "structures.glsl"
#include "common.glsl"

out vec3 v_normal;
out vec3 v_position;

void main(void)
{
    VSInput vin;
    SetVSInputParams;

    vec4 pos    = u_modelViewMatrix * vin.Position;
    v_normal    = u_normalMatrix * a_normal;
    gl_Position = u_projectionMatrix * pos;
}
