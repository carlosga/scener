// Partial port from the Microsoft XNA Stock Effects (Microsoft Permissive License.rtf)

#version 430 core

#define SKINNED_EFFECT_MAX_BONES   72

layout (location = 0) in vec3  VertexPosition;
layout (location = 1) in vec3  VertexNormal;
layout (location = 2) in vec3  VertexCoord;
layout (location = 3) in ivec4 BlendIndices;
layout (location = 4) in vec4  BlendWeights;

uniform mat4 World;
uniform mat4 WorldInverseTranspose;
uniform mat4 WorldViewProj;
uniform mat4 Bones[SKINNED_EFFECT_MAX_BONES];    // _vs(c26)          _cb(c22);
uniform uint WeightsPerVertex;

out vec3 PositionWS;
out vec3 NormalWS;
out vec3 TexCoord;

struct VSInputNmTxWeights
{
    vec4  Position;
    vec3  Normal;
    vec3  TexCoord;
    ivec4 Indices;
    vec4  Weights;
};

void Skin(inout VSInputNmTxWeights vin, uint boneCount)
{
    mat4 skinning = mat4(0.0f);

    for (int i = 0; i < boneCount; i++)
    {
        skinning += Bones[vin.Indices[i]] * vin.Weights[i];
    }

    vin.Position = skinning * vin.Position;
    vin.Normal   = (vec4(vin.Normal, 1.0) * skinning).xyz;
}

void main()
{
    VSInputNmTxWeights vin;

    vin.Position = vec4(VertexPosition, 1.0);
    vin.Normal   = VertexNormal;
    vin.TexCoord = VertexCoord;
    vin.Indices  = BlendIndices;
    vin.Weights  = BlendWeights;

    Skin(vin, WeightsPerVertex);

    gl_Position = vin.Position * WorldViewProj;
    PositionWS  = (vin.Position * World).xyz;
    NormalWS    = normalize(vec4(vin.Normal, 1.0) * WorldInverseTranspose).xyz;
    TexCoord    = VertexCoord;
}
