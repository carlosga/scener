// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/VertexPositionNormalTexture.hpp>

#include <Graphics/VertexDeclaration.hpp>

namespace SceneR
{
    namespace Graphics
    {
        using SceneR::Framework::Vector2;
        using SceneR::Framework::Vector3;

        const VertexDeclaration VertexPositionNormalTexture::declaration =
        {
            32
          , {
                { 0 , VertexElementFormat::Vector3, VertexElementUsage::Position, 0 }
              , { 12, VertexElementFormat::Vector3, VertexElementUsage::Normal, 1 }
              , { 24, VertexElementFormat::Vector2, VertexElementUsage::TextureCoordinate, 2 }
            }
        };

        VertexPositionNormalTexture::VertexPositionNormalTexture(const Vector3& position
                                                               , const Vector3& normal
                                                               , const Vector2& textureCoordinate)
            : position           { position }
            , normal             { normal }
            , texture_coordinate { textureCoordinate }
        {
        }

        VertexPositionNormalTexture::~VertexPositionNormalTexture()
        {
        }
    }
}
