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

using namespace System;
using namespace SceneR::Graphics;

VertexDeclaration::VertexDeclaration(const UInt32&                     componentCount,
                                     const UInt32&                     vertexStride,
                                     const std::vector<VertexElement>& vertexElements)
    : componentCount(componentCount), vertexStride(vertexStride), vertexElements(vertexElements)
{
}

const UInt32& VertexDeclaration::GetComponentCount() const
{
    return this->componentCount;
}

const UInt32& VertexDeclaration::GetVertexStride() const
{
    return this->vertexStride;
}

const std::vector<VertexElement>& VertexDeclaration::GetVertexElements() const
{
    return this->vertexElements;
}

