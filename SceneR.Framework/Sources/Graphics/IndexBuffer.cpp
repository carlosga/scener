// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/IndexBuffer.hpp>

using namespace System;
using namespace SceneR::Graphics;

IndexBuffer::IndexBuffer(GraphicsDevice&                           graphicsDevice
                       , const SceneR::Graphics::IndexElementSize& indexElementSize
                       , const UInt32&                             indexCount)
    : GraphicsResource { graphicsDevice }
    , ibo              { BufferTarget::ElementArraybuffer, BufferUsage::StaticDraw }
    , indexCount       { indexCount }
    , indexElementSize { indexElementSize }
{
}

IndexBuffer::~IndexBuffer()
{
}

void IndexBuffer::Dispose()
{
    this->ibo.Dispose();
}

const UInt32& IndexBuffer::IndexCount() const
{
    return this->indexCount;
}

const SceneR::Graphics::IndexElementSize& IndexBuffer::IndexElementSize() const
{
    return this->indexElementSize;
}

std::vector<uint8_t> IndexBuffer::GetData() const
{
    return this->GetData(0, this->indexCount);
}

std::vector<uint8_t> IndexBuffer::GetData(const UInt32& startIndex, const UInt32& elementCount) const
{
    auto offset = (startIndex * this->GetElementSizeInBytes());
    auto size   = (elementCount * this->GetElementSizeInBytes());
    auto data   = std::vector<uint8_t>(size);

    this->ibo.GetData(offset, size, data.data());

    return data;
}

void IndexBuffer::SetData(const void* data)
{
    this->ibo.BufferData(this->indexCount * this->GetElementSizeInBytes(), data);
}

void IndexBuffer::Activate() const
{
    this->ibo.Activate();
}

void IndexBuffer::Deactivate() const
{
    this->ibo.Deactivate();
}

UInt32 IndexBuffer::GetElementSizeInBytes() const
{
    return ((this->indexElementSize == SceneR::Graphics::IndexElementSize::SixteenBits) ? sizeof(UInt16) : sizeof(UInt32));
}
