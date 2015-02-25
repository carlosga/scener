// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/VertexPositionColorTexture.hpp>

#include <Graphics/VertexDeclaration.hpp>

using namespace SceneR::Framework;
using namespace SceneR::Graphics;

const VertexDeclaration& VertexPositionColorTexture::Declaration
{
    36
  , {
        { 0 , VertexElementFormat::Vector3, VertexElementUsage::Position, 0 }
      , { 12, VertexElementFormat::Vector4, VertexElementUsage::Color, 3 }
      , { 28, VertexElementFormat::Vector2, VertexElementUsage::TextureCoordinate, 2 }
    }
};

const VertexDeclaration& VertexPositionColorTexture::GetVertexDeclaration()
{
    return VertexPositionColorTexture::Declaration;
}

VertexPositionColorTexture::VertexPositionColorTexture(const Vector3&                  position
                                                     , const SceneR::Framework::Color& color
                                                     , const Vector2&                  textureCoordinate)
    : position          { position }
    , color             { color }
    , textureCoordinate { textureCoordinate }
{
}

VertexPositionColorTexture::~VertexPositionColorTexture()
{
}

const Vector3& VertexPositionColorTexture::Position() const
{
    return this->position;
}

const SceneR::Framework::Color& VertexPositionColorTexture::Color() const
{
    return this->color;
}

const Vector2& VertexPositionColorTexture::TextureCoordinate() const
{
    return this->textureCoordinate;
}
