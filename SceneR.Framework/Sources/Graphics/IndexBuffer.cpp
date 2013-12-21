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
#include <stdexcept>

using namespace System;
using namespace SceneR::Graphics;

IndexBuffer::IndexBuffer(GraphicsDevice&                           graphicsDevice,
                         const SceneR::Graphics::IndexElementSize& indexElementSize,
                         const UInt32&                             indexCount)
    : GraphicsResource(graphicsDevice),
      ibo(BufferTarget::ElementArraybuffer, BufferUsage::StaticDraw),
      indexCount(indexCount),
      indexElementSize(indexElementSize)
{
}

IndexBuffer::~IndexBuffer()
{
    this->ibo.Delete();
}

const UInt32& IndexBuffer::IndexCount() const
{
    return this->indexCount;
}

const SceneR::Graphics::IndexElementSize& IndexBuffer::IndexElementSize() const
{
    return this->indexElementSize;
}

const std::vector<UInt32>& IndexBuffer::GetData() const
{
    throw std::runtime_error("Not implemented");
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

const UInt32 IndexBuffer::GetElementSizeInBytes() const
{
    return ((this->indexElementSize == IndexElementSize::SixteenBits) ? sizeof(UInt16) : sizeof(UInt32));
}
