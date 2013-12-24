#version 430 core

in vec3 Position;
in vec3 Normal;

uniform bool EnableDefaultLighting;

struct DirectionalLightInfo 
{
    bool Enabled;
    vec3 Direction;
    vec3 DiffuseColor;
    vec3 SpecularColor;
};

layout (std140) uniform DirectionalLights
{
    DirectionalLightInfo DirectionalLight[3];
};

layout (location = 0) out vec4 FragColor;

void main() 
{
    FragColor = vec4(1.0);    
}