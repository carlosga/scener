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

#include <Content/Readers/VertexBufferReader.hpp>
#include <Graphics/VertexBuffer.hpp>
#include <Content/Readers/VertexDeclarationReader.hpp>
#include <Graphics/IGraphicsDeviceService.hpp>
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
