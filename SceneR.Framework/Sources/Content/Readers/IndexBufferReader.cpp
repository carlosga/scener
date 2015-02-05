// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/IndexBufferReader.hpp>

#include <Graphics/IndexBuffer.hpp>
#include <Graphics/IGraphicsDeviceService.hpp>
#include <Framework/RendererServiceContainer.hpp>
#include <Content/ContentManager.hpp>

using namespace System;
using namespace SceneR::Content;
using namespace SceneR::Graphics;

std::shared_ptr<void> IndexBufferReader::Read(ContentReader& input)
{
    auto& gdService     = input.ContentManager().ServiceProvider().GetService<IGraphicsDeviceService>();
    auto  isSixteenBits = input.ReadBoolean();
    auto  dataSize      = input.ReadUInt32();
    auto  elementSize   = ((isSixteenBits) ? IndexElementSize::SixteenBits : IndexElementSize::ThirtyTwoBits);
    auto  elementBytes  = ((isSixteenBits) ? sizeof(UInt16) : sizeof(UInt32));
    auto  buffer        = std::make_shared<IndexBuffer>(gdService.CurrentGraphicsDevice(), elementSize, (dataSize / elementBytes));
    auto  data          = input.ReadBytes(dataSize);

    buffer->SetData(data.data());

    return buffer;
}
