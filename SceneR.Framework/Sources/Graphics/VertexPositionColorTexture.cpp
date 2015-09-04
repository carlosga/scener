// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/VertexPositionColorTexture.hpp>

#include <Graphics/VertexDeclaration.hpp>

namespace SceneR
{
    namespace Graphics
    {
        using SceneR::Framework::Color;
        using SceneR::Framework::Vector2;
        using SceneR::Framework::Vector3;

        const VertexDeclaration VertexPositionColorTexture::declaration =
        {
            36
          , {
                { 0 , VertexElementFormat::Vector3, VertexElementUsage::Position, 0 }
              , { 12, VertexElementFormat::Vector4, VertexElementUsage::Color, 3 }
              , { 28, VertexElementFormat::Vector2, VertexElementUsage::TextureCoordinate, 2 }
            }
        };

        VertexPositionColorTexture::VertexPositionColorTexture(const Vector3&                  position
                                                             , const SceneR::Framework::Color& color
                                                             , const Vector2&                  textureCoordinate)
            : position           { position }
            , color              { color }
            , texture_coordinate { textureCoordinate }
        {
        }

        VertexPositionColorTexture::~VertexPositionColorTexture()
        {
        }
    }
}
