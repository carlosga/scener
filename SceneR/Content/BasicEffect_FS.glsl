#version 430 core

in vec3 Position;
in vec3 Normal;

uniform vec4 LightPosition;
uniform vec3 LightIntensity;
uniform vec3 Ka;          // Ambient reflectivity
uniform vec3 Kd;          // Diffuse reflectivity
uniform vec3 Ks;          // Specular reflectivity
uniform float Shininess;  // Specular shininess factor

layout (location = 0) out vec4 FragColor;

vec3 ads()
{
    vec3 s = normalize(LightPosition.xyz - Position);
    vec3 v = normalize(-Position.xyz);
    vec3 n = normalize(Normal);
    vec3 h = normalize(v + s);
    
    vec3 diffuse  = Ka + Kd * LightIntensity * max(0.0, dot(n, s));
    vec3 specular = Ks * pow(max(0.0, dot(n, h)), Shininess);

    return diffuse + specular;
}

void main() 
{
    FragColor = vec4(ads(), 1.0);    
}