vec4 sample_texture(sampler2D texture, vec2 texCoord)
{
    return textureLod(texture, texCoord, textureQueryLod(texture, texCoord).t);
}
