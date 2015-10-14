#version 440 core
#extension GL_ARB_shading_language_include : require
#pragma optionNV (unroll all)

in vec3 v_normal;
in vec2 v_texcoord0;

layout (binding = 0) uniform sampler2D u_diffuse;

#include "/earthshaker/earthshaker0CB.glsl"

layout (location = 0) out vec4 FragColor;

void main(void)
{
    vec3 normal   = normalize(v_normal);
    vec4 color    = vec4(0., 0., 0., 0.);
    vec4 diffuse  = texture2D(u_diffuse, v_texcoord0);
    vec4 emission = vec4(0., 0., 0., 0.); // u_emission;
    vec4 ambient  = u_ambient;
    vec4 specular = u_specular;

    diffuse.xyz *= max(dot(normal,vec3(0.8,0.8,1.)), 0.8);
    color.xyz   += diffuse.xyz;
    color.xyz   += emission.xyz;
    FragColor    = vec4(color.rgb * diffuse.a, diffuse.a);
}
