#version 440 core
#extension GL_ARB_shading_language_include : require
#pragma optionNV (unroll all)

in vec3 v_light0Direction;
in vec3 v_normal;
in vec3 v_position;
in vec2 v_texcoord0;

layout (binding = 0) uniform sampler2D u_diffuse;

#include "/earthshaker/earthshaker2CB.glsl"

layout (location = 0) out vec4 FragColor;

void main(void)
{
    vec3 normal       = normalize(v_normal);
    vec4 color        = vec4(0., 0., 0., 0.);
    vec4 diffuse      = texture2D(u_diffuse, v_texcoord0);
    vec3 diffuseLight = vec3(0.6, 0.6, 0.6);
    vec4 emission     = u_emission;
    vec4 ambient      = u_ambient;
    vec4 specular     = u_specular;

    vec3 specularLight = vec3(0., 0., 0.);
    {
    float specularIntensity = 0.;
    float attenuation       = 1.0;
    float range             = length(v_light0Direction);

    attenuation = 1.0 / (u_light0ConstantAttenuation + (u_light0LinearAttenuation * range) + (u_light0QuadraticAttenuation * range * range));

    vec3  l         = normalize(v_light0Direction);
    vec3  position  = v_position;
    float phongTerm = max(0.0, dot(reflect(-l, normal), normalize(-position)));

    specularIntensity = max(0., pow(phongTerm , u_shininess)) * attenuation;
    specularLight    += u_light0Color * specularIntensity;
    diffuseLight     += u_light0Color * max(dot(normal,l), 0.) * attenuation;
    }

    specular.xyz *= specularLight;
    color.xyz    += specular.xyz;
    diffuse.xyz  *= diffuseLight;
    color.xyz    += diffuse.xyz;
    color.xyz    += emission.xyz;
    color         = vec4(color.rgb * diffuse.a, diffuse.a);
    FragColor     = color;
}
