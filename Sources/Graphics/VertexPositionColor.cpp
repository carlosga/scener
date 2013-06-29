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

#include <vector>
#include "Graphics/VertexPositionColor.hpp"
#include "Graphics/VertexElementFormat.hpp"
#include "Graphics/VertexElementUsage.hpp"

using namespace SceneR::Core;
using namespace SceneR::Graphics;

const VertexDeclaration VertexPositionColor::GetVertexDeclaration()
{
    std::vector<VertexElement> vertexElements;

    vertexElements.push_back(VertexElement(0 , 3, VertexElementFormat::Vector3, VertexElementUsage::Position, 0));
    vertexElements.push_back(VertexElement(12, 4, VertexElementFormat::Vector4, VertexElementUsage::Color, 3));

    return VertexDeclaration(7, 28, vertexElements);
}

VertexPositionColor::VertexPositionColor(const Vector3& position,
                                         const Color&   color)
{
}

const Vector3& VertexPositionColor::GetPosition() const
{
    return this->position;
}

const Color& VertexPositionColor::GetColor() const
{
    return this->color;
}
