layout (binding = 0, std140) uniform ConstantBuffer
{
    mat4  u_jointMat[59];
    mat3  u_normalMatrix;
    mat4  u_modelViewMatrix;
    mat4  u_projectionMatrix;

    vec4  u_ambient;
    vec4  u_emission;
};
