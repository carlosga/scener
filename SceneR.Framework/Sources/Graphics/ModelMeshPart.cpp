// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/ModelMeshPart.hpp>

#include <Graphics/Effect.hpp>
#include <Graphics/IndexBuffer.hpp>
#include <Graphics/VertexBuffer.hpp>

using namespace System;
using namespace SceneR::Graphics;

ModelMeshPart::ModelMeshPart()
    : effect         { nullptr }
    , indexBuffer    { nullptr }
    , vertexBuffer   { nullptr }
    , startIndex     { 0 }
    , vertexOffset   { 0 }
    , vertexCount    { 0 }
    , primitiveCount { 0 }
    , tag            { u"" }
{
}

ModelMeshPart::~ModelMeshPart()
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

const std::shared_ptr<SceneR::Graphics::VertexBuffer>& ModelMeshPart::VertexBuffer() const
{
    return this->vertexBuffer;
}

std::size_t ModelMeshPart::StartIndex() const
{
    return this->startIndex;
}

std::size_t ModelMeshPart::VertexOffset() const
{
    return this->vertexOffset;
}

std::size_t ModelMeshPart::VertexCount() const
{
    return this->vertexCount;
}

std::size_t ModelMeshPart::PrimitiveCount() const
{
    return this->primitiveCount;
}

const std::u16string& ModelMeshPart::Tag() const
{
    return this->tag;
}

void ModelMeshPart::Tag(const std::u16string& tag)
{
    this->tag = tag;
}
