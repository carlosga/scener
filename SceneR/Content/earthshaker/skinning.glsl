//
// Skinning functions.
//

void skin(inout VSInputNmTxWeights vin, int boneCount)
{
    mat4 skinning = mat4(0.0f);

    for (int i = 0; i < boneCount; i++)
    {
        skinning += vin.Weights[i] * u_jointMat[int(vin.Indices[i])];
    }

    vin.Position = u_modelViewMatrix * skinning * vin.Position;
    vin.Normal   = mat3(u_normalMatrix) * mat3(skinning) * vin.Normal;
}