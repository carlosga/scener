// Partial port from the Microsoft XNA Stock Effects (Microsoft Permissive License.rtf)

#version 430 core

in vec4 Diffuse;
in vec4 Specular;

layout (location = 0) out vec4 FragColor;

void AddSpecular(inout vec4 color, vec3 specular)
{
    color.rgb += specular * color.a;
}

// Pixel shader: vertex lighting.
vec4 PSBasicVertexLighting(vec4 diffuse, vec4 specular)
{
    vec4 color = diffuse;

    AddSpecular(color, specular.rgb);
    
    return color;
}

void main() 
{
    FragColor = PSBasicVertexLighting(Diffuse, Specular);    
}