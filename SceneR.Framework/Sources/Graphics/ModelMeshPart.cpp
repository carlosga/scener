// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

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
