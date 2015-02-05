// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/VertexPositionNormalTexture.hpp>

#include <Graphics/VertexDeclaration.hpp>

using namespace SceneR::Framework;
using namespace SceneR::Graphics;

const VertexDeclaration& VertexPositionNormalTexture::Declaration
{
    32
  , {
        { 0 , VertexElementFormat::Vector3, VertexElementUsage::Position, 0 }
      , { 12, VertexElementFormat::Vector3, VertexElementUsage::Normal, 1 }
      , { 24, VertexElementFormat::Vector2, VertexElementUsage::TextureCoordinate, 2 }
    }
};

const VertexDeclaration& VertexPositionNormalTexture::GetVertexDeclaration()
{
    return VertexPositionNormalTexture::Declaration;
}

VertexPositionNormalTexture::VertexPositionNormalTexture(const Vector3& position
                                                       , const Vector3& normal
                                                       , const Vector2& textureCoordinate)
    : position          { position }
    , normal            { normal }
    , textureCoordinate { textureCoordinate }
{
}

const Vector3& VertexPositionNormalTexture::Position() const
{
    return this->position;
}

const Vector3& VertexPositionNormalTexture::Normal() const
{
    return this->normal;
}

const Vector2& VertexPositionNormalTexture::TextureCoordinate() const
{
    return this->textureCoordinate;
}
