#version 440 core

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;
layout (location = 2) in vec3 VertexCoord;
       
uniform mat4 World;
uniform mat4 WorldInverseTranspose;
uniform mat4 WorldViewProj;

out vec3 PositionWS;
out vec3 NormalWS;
out vec3 TexCoord;

void main() 
{
    gl_Position = vec4(VertexPosition, 1.0) * WorldViewProj;
    PositionWS  = (vec4(VertexPosition, 1.0) * World).xyz;
    NormalWS    = normalize(vec4(VertexNormal, 1.0) * WorldInverseTranspose).xyz;
    TexCoord    = VertexCoord;       
}
