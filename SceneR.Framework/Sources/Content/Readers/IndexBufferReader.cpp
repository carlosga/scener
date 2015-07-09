// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/IndexBufferReader.hpp>

#include <cstdint>

#include <Content/ContentManager.hpp>
#include <Content/ContentReader.hpp>
#include <Framework/RendererServiceContainer.hpp>
#include <Graphics/IGraphicsDeviceService.hpp>
#include <Graphics/IndexBuffer.hpp>

namespace SceneR
{
    namespace Content
    {
        using SceneR::Graphics::IGraphicsDeviceService;
        using SceneR::Graphics::IndexBuffer;
        using SceneR::Graphics::IndexElementSize;

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
            auto  elementBytes  = ((isSixteenBits) ? sizeof(std::uint16_t) : sizeof(std::uint32_t));
            auto  indexCount    = (dataSize / elementBytes);
            auto  buffer        = std::make_shared<IndexBuffer>(gdService.CurrentGraphicsDevice(), elementSize, indexCount);
            auto  data          = input.ReadBytes(dataSize);

            buffer->SetData(data.data());

            return buffer;
        }
    }
}
