layout (binding = 0, std140) uniform ConstantBuffer
{
    // Vertex Shader
    uniform mat4 u_normalMatrix;
    uniform mat4 u_modelViewMatrix;
    uniform mat4 u_projectionMatrix;

    // Fragment Shader
    uniform vec4  u_diffuse;
    uniform vec4  u_ambient;
    uniform vec4  u_emission;
    uniform vec4  u_specular;
    uniform float u_shininess;
};
