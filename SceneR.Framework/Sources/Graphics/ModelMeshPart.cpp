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

#include <Graphics/ModelMeshPart.hpp>

using namespace System;
using namespace SceneR::Graphics;

ModelMeshPart::ModelMeshPart()
    : effect(nullptr),       indexBuffer(nullptr), vertexCount(0), primitiveCount(0), startIndex(0), tag(),
      vertexBuffer(nullptr), vertexOffset(0)
{
}

ModelMeshPart::~ModelMeshPart()
{
}

std::shared_ptr<Effect> ModelMeshPart::GetEffect() const
{
    return this->effect;
}

void ModelMeshPart::SetEffect(const std::shared_ptr<Effect>& effect)
{
    this->effect = effect;
}

std::shared_ptr<IndexBuffer> ModelMeshPart::GetIndexBuffer()
{
    return this->indexBuffer;
}

const Int32& ModelMeshPart::GetVertexCount() const
{
    return this->vertexCount;
}

const Int32& ModelMeshPart::GetPrimitiveCount() const
{
    return this->primitiveCount;
}

const Int32& ModelMeshPart::GetStartIndex() const
{
    return this->startIndex;
}

const std::wstring& ModelMeshPart::GetTag() const
{
    return this->tag;
}

void ModelMeshPart::SetTag(const std::wstring& tag)
{
    this->tag = tag;
}

std::shared_ptr<VertexBuffer> ModelMeshPart::GetVertexBuffer()
{
    return this->vertexBuffer;
}

const Int32& ModelMeshPart::GetVertexOffset() const
{
    return this->vertexOffset;
}
