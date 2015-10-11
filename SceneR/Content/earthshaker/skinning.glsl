//
// Skinning functions.
//

void skin(inout VSInputNmTxWeights vin, int boneCount)
{
    mat4 skinning = mat4(0.0f);

    for (int i = 0; i < boneCount; i++)
    {
        skinning += u_jointMat[int(vin.Indices[i])] * vin.Weights[i];
    }

    vin.Position = vin.Position * skinning * u_modelViewMatrix;
    vin.Normal   = vin.Normal * mat3(skinning) * mat3(u_normalMatrix);
}
