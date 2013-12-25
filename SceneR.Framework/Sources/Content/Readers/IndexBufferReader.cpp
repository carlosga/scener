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

#include <Content/ContentManager.hpp>
#include <Content/ContentReader.hpp>
#include <Content/Readers/IndexBufferReader.hpp>
#include <Framework/RendererServiceContainer.hpp>
#include <Graphics/IGraphicsDeviceService.hpp>
#include <Graphics/IndexBuffer.hpp>
#include <Graphics/IndexElementSize.hpp>
#include <vector>

using namespace System;
using namespace SceneR::Content;
using namespace SceneR::Graphics;

IndexBufferReader::IndexBufferReader()
{
}

std::shared_ptr<void> IndexBufferReader::Read(ContentReader& input)
{
    auto&   gdService     = input.ContentManager().ServiceProvider().GetService<IGraphicsDeviceService>();
    Boolean isSixteenBits = input.ReadBoolean();
    UInt32  dataSize      = input.ReadUInt32();
    auto    elementSize   = ((isSixteenBits) ? IndexElementSize::SixteenBits : IndexElementSize::ThirtyTwoBits);
    UInt32  elementBytes  = ((isSixteenBits) ? sizeof(UInt16) : sizeof(UInt32));
    auto    buffer        = std::make_shared<IndexBuffer>(gdService.CurrentGraphicsDevice(), elementSize, (dataSize / elementBytes));
    auto    data          = input.ReadBytes(dataSize);

    buffer->SetData(data.data());

    return buffer;
}
