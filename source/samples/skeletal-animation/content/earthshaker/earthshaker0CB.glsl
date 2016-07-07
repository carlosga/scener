layout (binding = 0, std140) uniform ConstantBuffer
{
    // Vertex Shader
    uniform mat4 u_jointMat[57];
    uniform mat4 u_normalMatrix;
    uniform mat4 u_modelViewMatrix;
    uniform mat4 u_projectionMatrix;
    uniform mat4 u_light0Transform;

    // Fragment Shader
    uniform vec4  u_ambient;
    uniform vec4  u_emission;
    uniform vec4  u_specular;
    uniform float u_shininess;
    uniform float u_light0ConstantAttenuation;
    uniform float u_light0LinearAttenuation;
    uniform float u_light0QuadraticAttenuation;
    uniform vec3  u_light0Color;
};
