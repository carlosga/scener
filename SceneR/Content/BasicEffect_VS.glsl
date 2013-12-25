// Partial port from the Microsoft XNA Stock Effects (Microsoft Permissive License.rtf)

#version 430 core

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;
layout (location = 2) in vec3 VertexTextureCoordinate;
layout (location = 3) in vec4 BlendIndices;
layout (location = 4) in vec4 BlendWeights;

//layout (std140, row_major) uniform Parameters   // cbuffer Parameters : register(b0)
//{
    uniform vec4  DiffuseColor;             // _vs(c0)  _ps(c1)  _cb(c0);
    uniform vec3  EmissiveColor;            // _vs(c1)  _ps(c2)  _cb(c1);
    uniform vec3  SpecularColor;            // _vs(c2)  _ps(c3)  _cb(c2);
    uniform float SpecularPower;            // _vs(c3)  _ps(c4)  _cb(c2.w);

    uniform vec3  DirLight0Direction;       // _vs(c4)  _ps(c5)  _cb(c3);
    uniform vec3  DirLight0DiffuseColor;    // _vs(c5)  _ps(c6)  _cb(c4);
    uniform vec3  DirLight0SpecularColor;   // _vs(c6)  _ps(c7)  _cb(c5);

    uniform vec3  DirLight1Direction;       // _vs(c7)  _ps(c8)  _cb(c6);
    uniform vec3  DirLight1DiffuseColor;    // _vs(c8)  _ps(c9)  _cb(c7);
    uniform vec3  DirLight1SpecularColor;   // _vs(c9)  _ps(c10) _cb(c8);
    
    uniform vec3  DirLight2Direction;       // _vs(c10) _ps(c11) _cb(c9);
    uniform vec3  DirLight2DiffuseColor;    // _vs(c11) _ps(c12) _cb(c10);
    uniform vec3  DirLight2SpecularColor;   // _vs(c12) _ps(c13) _cb(c11);   

    uniform vec3  EyePosition;              // _vs(c13) _ps(c14) _cb(c12);
    
    uniform vec3  FogColor;                 //          _ps(c0)  _cb(c13);
    uniform vec4  FogVector;                // _vs(c14)          _cb(c14);

    uniform mat4  World;                    // _vs(c19)          _cb(c15);
    uniform mat4  WorldInverseTranspose;    // _vs(c23)          _cb(c19);
//};

//layout (std140, row_major) uniform ProjectionMatrix // cbuffer ProjectionMatrix : register(b1)
//{
    uniform mat4 WorldViewProj;             // _vs(c15)          _cb(c0);
//};

// out vec4 PositionPS;
// out vec3 Normal;
// out vec3 TexCoord;
out vec4 Diffuse;
out vec4 Specular;

out struct CommonVSOutput
{
    vec4  Pos_ps;
    vec4  Diffuse;
    vec3  Specular;
    float FogFactor;
};

struct ColorPair
{
    vec3 Diffuse;
    vec3 Specular;
};

float ComputeFogFactor(vec4 position)
{
    // return saturate(dot(position, FogVector));
    return clamp(dot(position, FogVector), 0.0, 1.0);
}

ColorPair ComputeLights(vec3 eyeVector, vec3 worldNormal, int numLights)
{
    mat3 lightDirections = mat3(0.0);
    mat3 lightDiffuse    = mat3(0.0);
    mat3 lightSpecular   = mat3(0.0);
    mat3 halfVectors     = mat3(0.0);
    
    for (int i = 0; i < numLights; i++)
    {
        lightDirections[i] = mat3(DirLight0Direction,     DirLight1Direction,     DirLight2Direction)[i];
        lightDiffuse[i]    = mat3(DirLight0DiffuseColor,  DirLight1DiffuseColor,  DirLight2DiffuseColor)[i];
        lightSpecular[i]   = mat3(DirLight0SpecularColor, DirLight1SpecularColor, DirLight2SpecularColor)[i];        
        halfVectors[i]     = normalize(eyeVector - lightDirections[i]);
    }
        
    vec3 dotL     = -lightDirections * worldNormal;
    vec3 dotH     = halfVectors * worldNormal;    
    vec3 zeroL    = step(0.0, dotL);
    vec3 diffuse  = zeroL * dotL;
    vec3 specular = vec3(pow(max(dot(dotH, zeroL), 0.0), SpecularPower));   // pow(max(dotH, 0) * zeroL, SpecularPower);                    
        
    ColorPair result;    
    
    result.Diffuse  = (diffuse *  lightDiffuse) * DiffuseColor.rgb + EmissiveColor;
    result.Specular = (specular * lightSpecular) * SpecularColor;

    return result;
}

CommonVSOutput ComputeCommonVSOutputWithLighting(vec4 position, vec3 normal, int numLights)
{
    CommonVSOutput vout;
    
    vec4 pos_ws      = position * World;
    vec3 eyeVector   = normalize(EyePosition - pos_ws.xyz);
    vec3 worldNormal = normalize(vec4(normal, 1.0) * WorldInverseTranspose).xyz;

    ColorPair lightResult = ComputeLights(eyeVector, worldNormal, numLights);
    
    vout.Pos_ps    = position * WorldViewProj;
    vout.Diffuse   = vec4(lightResult.Diffuse, DiffuseColor.a);
    vout.Specular  = lightResult.Specular;
    vout.FogFactor = ComputeFogFactor(position);
    
    return vout;
}

void main() 
{
    CommonVSOutput cout = ComputeCommonVSOutputWithLighting(vec4(VertexPosition, 1.0), VertexNormal, 3);

    // PositionPS = cout.Pos_ps;
    Diffuse    = cout.Diffuse;
    Specular   = vec4(cout.Specular, cout.FogFactor);
    // TexCoord   = VertexTextureCoordinate;
    
    gl_Position = cout.Pos_ps;
}