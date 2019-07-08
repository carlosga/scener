#version 450 core

#extension GL_GOOGLE_include_directive : require
#extension GL_ARB_separate_shader_objects : enable

in vec3 v_normal;
in vec3 v_position;

#include "Box0CB.glsl"
#include "common.glsl"

layout (location = 0) out vec4 FragColor;

void main(void)
{
    vec3 normal   = normalize(v_normal);
    vec4 color    = vec4(0., 0., 0., 0.);
    vec4 diffuse  = u_diffuse;
    vec4 specular = u_specular;

    diffuse.xyz *= max(dot(normal,vec3(0.,0.,1.)), 0.);
    color.xyz   += diffuse.xyz;
    color        = vec4(color.rgb * diffuse.a, diffuse.a);
    FragColor    = color;
}
