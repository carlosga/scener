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

#include <Graphics/BufferTarget.hpp>
#include <Graphics/BufferUsage.hpp>
#include <Graphics/IndexBuffer.hpp>

using namespace System;
using namespace SceneR::Graphics;

IndexBuffer::IndexBuffer(GraphicsDevice&                           graphicsDevice
                       , const SceneR::Graphics::IndexElementSize& indexElementSize
                       , const Size&                               indexCount)
    : GraphicsResource(graphicsDevice)
    , ibo(BufferTarget::ElementArraybuffer, BufferUsage::StaticDraw)
    , indexCount(indexCount)
    , indexElementSize(indexElementSize)
{
}

IndexBuffer::~IndexBuffer()
{
}

const Size& IndexBuffer::IndexCount() const
{
    return this->indexCount;
}

const SceneR::Graphics::IndexElementSize& IndexBuffer::IndexElementSize() const
{
    return this->indexElementSize;
}

std::vector<UByte> IndexBuffer::GetData() const
{
    return this->GetData(0, this->indexCount);
}

std::vector<UByte> IndexBuffer::GetData(const Size& startIndex, const Size& elementCount) const
{
    auto offset = (startIndex * this->GetElementSizeInBytes());
    auto size   = (elementCount * this->GetElementSizeInBytes());
    auto data   = std::vector<UByte>(size);

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

Size IndexBuffer::GetElementSizeInBytes() const
{
    return ((this->indexElementSize == SceneR::Graphics::IndexElementSize::SixteenBits) ? sizeof(UInt16) : sizeof(UInt32));
}
