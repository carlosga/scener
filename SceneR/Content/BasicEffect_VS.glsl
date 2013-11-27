#version 430

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;
layout (location = 2) in vec2 VertexCoord;

uniform mat4 WorldView;
uniform mat4 WorldViewProjection;
uniform mat4 WorldInverseTranspose;

out vec3 Position;
out vec3 Normal;
// out vec2 FragmentTexCoord;

void main() 
{
    // Pass the tex coord straight through to the fragment shader
    // FragmentTexCoord = VertexCoord;
    
    // Calculate the World Normal
    Normal = normalize(vec4(VertexNormal, 1.0) * WorldInverseTranspose).xyz;    
    
    // Calculate vertex position
    Position = (vec4(VertexPosition, 1.0) * WorldView).xyz;
    
    // Apply all matrix transformations to vert
    gl_Position = vec4(VertexPosition, 1.0) * WorldViewProjection;
}