layout (binding = 0, std140) uniform ConstantBuffer
{
    // Vertex Shader
    mat4 u_jointMat[59];
    mat3 u_normalMatrix;
    mat4 u_modelViewMatrix;
    mat4 u_projectionMatrix;
    mat4 u_light0Transform;

    // Fragment Shader
    vec4  u_ambient;
    vec4  u_emission;
    vec4  u_specular;
    float u_shininess;
    float u_light0ConstantAttenuation;
    float u_light0LinearAttenuation;
    float u_light0QuadraticAttenuation;
    vec3  u_light0Color;
};
