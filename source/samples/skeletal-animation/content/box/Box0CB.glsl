layout (binding = 0, std140) uniform ConstantBuffer
{
    uniform vec4  u_diffuse;
    uniform vec4  u_specular;
    uniform mat4  u_normalMatrix;
    uniform mat4  u_modelViewMatrix;
    uniform mat4  u_projectionMatrix;
};
