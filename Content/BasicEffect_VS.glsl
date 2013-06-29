#version 420

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
    
    // Transform the normal vector
    Normal = vec3(normalize(WorldInverseTranspose * vec4(VertexNormal, 1.0)));    
    
    // Calculate vertex position
    Position = vec3(WorldView * vec4(VertexPosition, 1.0));
    
    // Apply all matrix transformations to vert
    gl_Position = WorldViewProjection * vec4(VertexPosition, 1.0);
}