//-------------------------------------------------------------------------------
//Copyright 2013 Carlos Guzmán Álvarez
//
//Licensed under the Apache License, Version 2.0 (the "License");
//you may not use this file except in compliance with the License.
//You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//Unless required by applicable law or agreed to in writing, software
//distributed under the License is distributed on an "AS IS" BASIS,
//WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//See the License for the specific language governing permissions and
//limitations under the License.
//-------------------------------------------------------------------------------

#include <Graphics/VertexDeclaration.hpp>
#include <Graphics/VertexElement.hpp>
#include <Graphics/VertexElementFormat.hpp>
#include <Graphics/VertexElementUsage.hpp>
#include <Graphics/VertexPositionColorTexture.hpp>

using namespace SceneR::Framework;
using namespace SceneR::Graphics;

const VertexDeclaration& VertexPositionColorTexture::Declaration
{
    36
  , {
        VertexElement(0 , VertexElementFormat::Vector3, VertexElementUsage::Position, 0)
      , VertexElement(12, VertexElementFormat::Vector4, VertexElementUsage::Color, 3)
      , VertexElement(28, VertexElementFormat::Vector2, VertexElementUsage::TextureCoordinate, 2)
    }
};

const VertexDeclaration& VertexPositionColorTexture::GetVertexDeclaration()
{
    return VertexPositionColorTexture::Declaration;
}

VertexPositionColorTexture::VertexPositionColorTexture(const Vector3&                  position
                                                     , const SceneR::Framework::Color& color
                                                     , const Vector2&                  textureCoordinate)
    : position(position)
    , color(color)
    , textureCoordinate(textureCoordinate)
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
