vec4 sample_texture(sampler2D texture, vec2 texCoord)
{
    return textureLod(texture, texCoord, textureQueryLod(texture, texCoord).t);
}

//
// VS Input macros
//

#define SetVSInputNmTxWeightsParams \
    vin.Position = vec4(a_position, 1.0f); \
    vin.Normal   = a_normal; \
    vin.Indices  = a_joint; \
    vin.Weights  = a_weight;
