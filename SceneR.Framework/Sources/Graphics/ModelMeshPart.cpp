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
#include <Graphics/VertexBuffer.hpp>
#include <Graphics/IndexBuffer.hpp>
#include <Graphics/Effect.hpp>

using namespace System;
using namespace SceneR::Graphics;

ModelMeshPart::ModelMeshPart()
    : effect         { nullptr }
    , indexBuffer    { nullptr }
    , vertexCount    { 0 }
    , primitiveCount { 0 }
    , startIndex     { 0 }
    , tag            { u"" }
    , vertexBuffer   { nullptr }
    , vertexOffset   { 0 }
{
}

const std::shared_ptr<SceneR::Graphics::Effect>& ModelMeshPart::Effect() const
{
    return this->effect;
}

void ModelMeshPart::Effect(const std::shared_ptr<SceneR::Graphics::Effect>& effect)
{
    this->effect = effect;
}

const std::shared_ptr<SceneR::Graphics::IndexBuffer>& ModelMeshPart::IndexBuffer() const
{
    return this->indexBuffer;
}

const Size& ModelMeshPart::VertexCount() const
{
    return this->vertexCount;
}

const Size& ModelMeshPart::PrimitiveCount() const
{
    return this->primitiveCount;
}

const Size& ModelMeshPart::StartIndex() const
{
    return this->startIndex;
}

const String& ModelMeshPart::Tag() const
{
    return this->tag;
}

void ModelMeshPart::Tag(const String& tag)
{
    this->tag = tag;
}

const std::shared_ptr<SceneR::Graphics::VertexBuffer>& ModelMeshPart::VertexBuffer() const
{
    return this->vertexBuffer;
}

const Size& ModelMeshPart::VertexOffset() const
{
    return this->vertexOffset;
}
