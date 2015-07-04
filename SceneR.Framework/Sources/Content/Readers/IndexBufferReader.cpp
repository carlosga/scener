// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/IndexBufferReader.hpp>

#include <Content/ContentManager.hpp>
#include <Content/ContentReader.hpp>
#include <Framework/RendererServiceContainer.hpp>
#include <Graphics/IGraphicsDeviceService.hpp>
#include <Graphics/IndexBuffer.hpp>

using namespace System;
using namespace SceneR::Content;
using namespace SceneR::Graphics;

IndexBufferReader::IndexBufferReader()
{
}

IndexBufferReader::~IndexBufferReader()
{
}

std::shared_ptr<void> IndexBufferReader::Read(ContentReader& input)
{
    auto& gdService     = input.ContentManager().ServiceProvider().GetService<IGraphicsDeviceService>();
    auto  isSixteenBits = input.ReadBoolean();
    auto  dataSize      = input.ReadUInt32();
    auto  elementSize   = ((isSixteenBits) ? IndexElementSize::SixteenBits : IndexElementSize::ThirtyTwoBits);
    auto  elementBytes  = ((isSixteenBits) ? sizeof(uint16_t) : sizeof(UInt32));
    auto  indexCount    = (dataSize / elementBytes);
    auto  buffer        = std::make_shared<IndexBuffer>(gdService.CurrentGraphicsDevice(), elementSize, indexCount);
    auto  data          = input.ReadBytes(dataSize);

    buffer->SetData(data.data());

    return buffer;
}
