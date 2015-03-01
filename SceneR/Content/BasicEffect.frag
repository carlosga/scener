// Partial port from the Microsoft XNA Stock Effects (Microsoft Permissive License.rtf)

#version 440 core

in vec3 PositionWS;
in vec3 NormalWS;
in vec3 TexCoord;

layout (location = 0) out vec4 FragColor;

uniform sampler2D Texture;

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
//};

struct ColorPair
{
    vec3 Diffuse;
    vec3 Specular;
};

void AddSpecular(inout vec4 color, vec3 specular)
{
    color.rgb += specular * color.a;
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

        halfVectors[i]     = lightDirections[i] - eyeVector;
    }

    vec3 dotL = worldNormal * -lightDirections;
    vec3 dotH = normalize(worldNormal * -halfVectors);

    vec3 zeroL = step(0, dotL);

    vec3 diffuse  = zeroL * dotL;
    vec3 specular = pow(max(dotH, 0) * zeroL, vec3(SpecularPower));

    ColorPair result;

    result.Diffuse  = lightDiffuse * diffuse * DiffuseColor.rgb + EmissiveColor;
    result.Specular = lightSpecular * specular * SpecularColor;

    return result;
}

void main()
{
    vec4      diffuse     = vec4(1.0, 1.0, 1.0, DiffuseColor.a);
    vec4      color       = texture(Texture, TexCoord.st) * diffuse;
    vec3      eyeVector   = normalize(EyePosition - PositionWS.xyz);
    vec3      worldNormal = normalize(NormalWS);
    ColorPair lightResult = ComputeLights(eyeVector, worldNormal, 3);

    color.rgb *= lightResult.Diffuse;

    AddSpecular(color, lightResult.Specular);

    FragColor = color;
}
