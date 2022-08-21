#version 430 core

#extension GL_GOOGLE_include_directive : require
#extension GL_ARB_separate_shader_objects : enable

in vec3 v_normal;
in vec2 v_texcoord0;
in vec3 v_light0Direction;
in vec3 v_position;

layout (binding = 1) uniform sampler2D u_diffuse;

#include "earthshaker0CB.glsl"
#include "texture_sampling.glsl"
#include "common.glsl"

layout (location = 0) out vec4 FragColor;

void main(void)
{
    vec3 normal       = normalize(v_normal);
    vec4 color        = vec4(0., 0., 0., 0.);
    vec4 emission     = vec4(0., 0., 0., 0.);   // u_emission
    vec4 ambient      = u_ambient;
    vec4 specular     = u_specular;
    vec4 diffuse      = sample_texture(u_diffuse, v_texcoord0);
    vec3 diffuseLight = vec3(1., 1., 1.);

    vec3 specularLight = vec3(0., 0., 0.);

    float specularIntensity = 0.;
    float attenuation       = 1.0;
    float range             = length(v_light0Direction);

    attenuation = 1.0 / (u_light0ConstantAttenuation + (u_light0LinearAttenuation * range) + (u_light0QuadraticAttenuation * range * range));

    vec3 l          = normalize(v_light0Direction);
    vec3 viewDir    = -normalize(v_position);
    float phongTerm = max(0.0, dot(reflect(-l,normal), viewDir));

    specularIntensity = max(0., pow(phongTerm , u_shininess)) * attenuation;
    specularLight    += u_light0Color * specularIntensity;
    diffuseLight     += u_light0Color * max(dot(normal,l), 0.) * attenuation;

    specular.xyz *= specularLight;
    color.xyz    += specular.xyz;
    diffuse.xyz  *= diffuseLight;
    color.xyz    += diffuse.xyz;
    color.xyz    += emission.xyz;
    color         = vec4(color.rgb * diffuse.a, diffuse.a);

    FragColor = color;
}
