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
#include <Graphics/VertexBuffer.hpp>
#include <Graphics/VertexElement.hpp>
#include <Graphics/VertexElementFormat.hpp>
#include <Graphics/VertexElementUsage.hpp>
#include <System/IO/BinaryReader.hpp>
#include <System/IO/MemoryStream.hpp>

using namespace System;
using namespace System::IO;
using namespace SceneR::Graphics;

VertexBuffer::VertexBuffer(GraphicsDevice&                                      graphicsDevice
                         , System::UInt32                                       vertexCount
                         , std::shared_ptr<SceneR::Graphics::VertexDeclaration> vertexDeclaration)
    : GraphicsResource(graphicsDevice),
      vertexDeclaration(vertexDeclaration),
      vertexCount(vertexCount),
      vao(),
      vbo(BufferTarget::ArrayBuffer, BufferUsage::StaticDraw)
{
    this->vao.DeclareVertexFormat(*this->vertexDeclaration);
}

VertexBuffer::~VertexBuffer()
{
    this->vbo.Delete();
    this->vao.Delete();
}

const UInt32& VertexBuffer::VertexCount() const
{
    return this->vertexCount;
}

std::vector<UByte> VertexBuffer::GetData() const
{
    UInt32 size = (this->vertexCount * this->vertexDeclaration->VertexStride());
    std::vector<UByte> data(size);

    this->vbo.GetData(0, size, data.data());
//
//    MemoryStream stream(data);
//    BinaryReader reader(stream);
//
//    for (int i = 0; i < this->vertexCount; i++)
//    {
//        for (const VertexElement& ve : this->vertexDeclaration->VertexElements())
//        {
//            UInt32 componentCount;
//
//            switch (ve.VertexElementFormat())
//            {
//                case VertexElementFormat::Single:
//                    componentCount = 1;
//                    break;
//
//                case VertexElementFormat::Vector2:
//                case VertexElementFormat::Short2:
//                case VertexElementFormat::NormalizedShort2:
//                case VertexElementFormat::HalfVector2:
//                    componentCount = 2;
//                    break;
//
//                case VertexElementFormat::Vector3:
//                    componentCount = 3;
//                    break;
//
//                case VertexElementFormat::Vector4:
//                case VertexElementFormat::Color:
//                case VertexElementFormat::Byte4:
//                case VertexElementFormat::Short4:
//                case VertexElementFormat::NormalizedShort4:
//                case VertexElementFormat::HalfVector4:
//                    componentCount = 4;
//                    break;
//            }
//
//            for (int j = 0; j < componentCount; j++)
//            {
//                switch (ve.VertexElementFormat())
//                {
//                    case VertexElementFormat::Single:
//                    case VertexElementFormat::Vector2:
//                    case VertexElementFormat::Vector3:
//                    case VertexElementFormat::Color:
//                    case VertexElementFormat::Vector4:
//                        std::cout << reader.ReadSingle() << "  ";
//                        break;
//
//                    case VertexElementFormat::Short2:
//                    case VertexElementFormat::NormalizedShort2:
//                    case VertexElementFormat::HalfVector2:
//                    case VertexElementFormat::Short4:
//                    case VertexElementFormat::NormalizedShort4:
//                    case VertexElementFormat::HalfVector4:
//                        std::cout << reader.ReadUInt16() << "  ";
//                        break;
//
//                    case VertexElementFormat::Byte4:
//                        std::cout << (UInt16)reader.ReadByte() << "  ";
//                        break;
//                }
//            }
//
//            std::cout << " || ";
//        }
//
//        std::cout << " || " << std::endl;
//    }

    return data;
}

void VertexBuffer::SetData(const void* data)
{
    this->vbo.BufferData(this->vertexCount * this->vertexDeclaration->VertexStride(), data);
}

std::shared_ptr<SceneR::Graphics::VertexDeclaration> VertexBuffer::VertexDeclaration()
{
    return this->vertexDeclaration;
}

void VertexBuffer::Activate()
{
    this->vao.Activate();

    glBindVertexBuffer(0, this->vbo.Id(), 0, this->vertexDeclaration->VertexStride());
}

void VertexBuffer::Deactivate()
{
    glBindVertexBuffer(0, 0, 0, this->vertexDeclaration->VertexStride());

    this->vao.Deactivate();
}
