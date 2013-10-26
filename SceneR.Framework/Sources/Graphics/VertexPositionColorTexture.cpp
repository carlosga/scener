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
#include <vector>

using namespace SceneR::Framework;
using namespace SceneR::Graphics;

const VertexDeclaration VertexPositionColorTexture::GetVertexDeclaration()
{
    std::vector<VertexElement> vertexElements;

    vertexElements.push_back(VertexElement(0 , 3, VertexElementFormat::Vector3, VertexElementUsage::Position, 0));
    vertexElements.push_back(VertexElement(12, 4, VertexElementFormat::Vector4, VertexElementUsage::Color, 3));
    vertexElements.push_back(VertexElement(28, 2, VertexElementFormat::Vector3, VertexElementUsage::TextureCoordinate, 2));

    return VertexDeclaration(9, 36, vertexElements);
}

VertexPositionColorTexture::VertexPositionColorTexture(const Vector3& position, const Color& color, const Vector2& textureCoordinate)
    : position(position), color(color), textureCoordinate(textureCoordinate)
{
}

const Vector3& VertexPositionColorTexture::GetPosition() const
{
    return this->position;
}

const Color& VertexPositionColorTexture::GetColor() const
{
    return this->color;
}

const Vector2& VertexPositionColorTexture::GetTextureCoordinate() const
{
    return this->textureCoordinate;
}
