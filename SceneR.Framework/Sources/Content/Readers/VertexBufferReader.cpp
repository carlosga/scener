// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/VertexBufferReader.hpp>

#include <Graphics/IGraphicsDeviceService.hpp>
#include <Content/Readers/VertexDeclarationReader.hpp>
#include <Graphics/VertexBuffer.hpp>
#include <Framework/RendererServiceContainer.hpp>
#include <Content/ContentManager.hpp>

using namespace System;
using namespace SceneR::Framework;
using namespace SceneR::Content;
using namespace SceneR::Graphics;

std::shared_ptr<void> VertexBufferReader::Read(ContentReader& input)
{
    auto& gdService   = input.ContentManager().ServiceProvider().GetService<IGraphicsDeviceService>();
    auto  vDecl       = this->ReadVertexDeclaration(input);
    auto  vertexCount = input.ReadUInt32();
    auto  buffer      = std::make_shared<VertexBuffer>(gdService.CurrentGraphicsDevice(), vertexCount, vDecl);
    auto  data        = input.ReadBytes(buffer->VertexCount() * vDecl->VertexStride());

    buffer->SetData(data.data());

    return buffer;
}

std::shared_ptr<VertexDeclaration> VertexBufferReader::ReadVertexDeclaration(ContentReader& input)
{
    auto reader = VertexDeclarationReader { };
    return std::static_pointer_cast<VertexDeclaration>(reader.Read(input));
}
