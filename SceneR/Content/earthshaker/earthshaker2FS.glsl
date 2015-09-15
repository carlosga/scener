#version 440 core
#extension GL_ARB_shading_language_include : require
#pragma optionNV (unroll all)

in vec3 v_normal;
in vec2 v_texcoord0;

layout (binding = 0) uniform sampler2D u_diffuse;

#include "/earthshaker/earthshaker2CB.glsl"

layout (location = 0) out vec4 FragColor;

void main(void)
{
    vec3 normal = normalize(v_normal);
    vec4 color = vec4(0., 0., 0., 0.);
    vec4 diffuse = vec4(0., 0., 0., 1.);
    vec4 emission;
    vec4 ambient;
    ambient = u_ambient;
    diffuse = textureLod(u_diffuse, v_texcoord0, textureQueryLod(u_diffuse, v_texcoord0).t);
    emission = u_emission;
    diffuse.xyz *= max(dot(normal,vec3(1.,1.,1.)), 1.);
    color.xyz += diffuse.xyz;
    color.xyz += emission.xyz;
    color = vec4(color.rgb * diffuse.a, diffuse.a);
    FragColor = color;
}
