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

#include "Graphics/VertexPositionNormalTexture.hpp"
#include "Graphics/VertexElement.hpp"
#include "Graphics/VertexElementFormat.hpp"
#include "Graphics/VertexElementUsage.hpp"

using namespace SceneR::Core;
using namespace SceneR::Graphics;

const VertexDeclaration VertexPositionNormalTexture::GetVertexDeclaration()
{
    std::vector<VertexElement> vertexElements;

    vertexElements.push_back(VertexElement(0 , 3, VertexElementFormat::Vector3, VertexElementUsage::Position, 0));
    vertexElements.push_back(VertexElement(12, 3, VertexElementFormat::Vector3, VertexElementUsage::Normal, 1));
    vertexElements.push_back(VertexElement(24, 2, VertexElementFormat::Vector2, VertexElementUsage::TextureCoordinate, 2));

    return VertexDeclaration(8, 32, vertexElements);
}

VertexPositionNormalTexture::VertexPositionNormalTexture(const Vector3& position,
                                                         const Vector3& normal,
                                                         const Vector2& textureCoordinate)
    : position(position),
      normal(normal),
      textureCoordinate(textureCoordinate)
{
}

const Vector3& VertexPositionNormalTexture::GetPosition() const
{
    return this->position;
}

const Vector3& VertexPositionNormalTexture::GetNormal() const
{
    return this->normal;
}

const Vector2& VertexPositionNormalTexture::GetTextureCoordinate() const
{
    return this->textureCoordinate;
}
