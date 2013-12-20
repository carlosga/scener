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
#include <Graphics/VertexPositionNormalTexture.hpp>

using namespace SceneR::Framework;
using namespace SceneR::Graphics;

const VertexDeclaration& VertexPositionNormalTexture::Declaration
{
    8,
    32,
    {
        VertexElement(0 , VertexElementFormat::Vector3, VertexElementUsage::Position, 0),
        VertexElement(12, VertexElementFormat::Vector3, VertexElementUsage::Normal, 1),
        VertexElement(24, VertexElementFormat::Vector2, VertexElementUsage::TextureCoordinate, 2)
    }
};

const VertexDeclaration& VertexPositionNormalTexture::GetVertexDeclaration()
{
    return VertexPositionNormalTexture::Declaration;
}

VertexPositionNormalTexture::VertexPositionNormalTexture(const Vector3& position,
                                                         const Vector3& normal,
                                                         const Vector2& textureCoordinate)
    : position(position), normal(normal), textureCoordinate(textureCoordinate)
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
