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

#include <Framework/BoundingSphere.hpp>
#include <Graphics/GraphicsDevice.hpp>
#include <Graphics/IndexBuffer.hpp>
#include <Graphics/ModelMesh.hpp>
#include <Graphics/PrimitiveType.hpp>
#include <Graphics/VertexBuffer.hpp>
#include <memory>
#include <string>

using namespace System;
using namespace SceneR::Graphics;

ModelMesh::ModelMesh()
    : meshParts(0), name(), parentBone(nullptr), tag()
{
}

ModelMesh::~ModelMesh()
{
}

const std::shared_ptr<SceneR::Framework::BoundingSphere>& ModelMesh::BoundingSphere()
{
    return this->boundingSphere;
}

void ModelMesh::Draw()
{
    for (auto& meshPart : this->meshParts)
    {
        auto graphicsDevice = meshPart->VertexBuffer()->CurrentGraphicsDevice();

        if (meshPart->Effect() != nullptr)
        {
            graphicsDevice.Effect(meshPart->Effect());
        }

        graphicsDevice.VertexBuffer(meshPart->VertexBuffer());
        graphicsDevice.IndexBuffer(meshPart->IndexBuffer());
        graphicsDevice.DrawIndexedPrimitives(PrimitiveType::TriangleList,
                                             0,
                                             0,
                                             meshPart->VertexCount(),
                                             meshPart->StartIndex(),
                                             meshPart->PrimitiveCount());
    }
}

const std::vector<std::shared_ptr<Effect>> ModelMesh::Effects()
{
    auto effects = std::vector<std::shared_ptr<Effect>>(0);

    for (auto &meshPart : this->meshParts)
    {
        if (meshPart->Effect() != nullptr)
        {
            effects.push_back(meshPart->Effect());
        }
    }

    return effects;
}

const std::vector<std::shared_ptr<ModelMeshPart>>& ModelMesh::MeshParts() const
{
    return this->meshParts;
}

const String& ModelMesh::Name() const
{
    return this->name;
}

void ModelMesh::Name(const String& name)
{
    this->name = name;
}

std::shared_ptr<ModelBone> ModelMesh::ParentBone() const
{
    return this->parentBone;
}

const String& ModelMesh::Tag() const
{
    return this->tag;
}

void ModelMesh::Tag(const String& tag)
{
    this->tag = tag;
}


//this->vbo.GetData(0, size, data.data());
//
//MemoryStream stream(data);
//BinaryReader reader(stream);
//
//for (int i = 0; i < this->vertexCount; i++)
//{
//    for (const VertexElement& ve : this->vertexDeclaration->VertexElements())
//    {
//        UInt32 componentCount;
//
//        switch (ve.VertexElementFormat())
//        {
//            case VertexElementFormat::Single:
//                componentCount = 1;
//                break;
//
//            case VertexElementFormat::Vector2:
//            case VertexElementFormat::Short2:
//            case VertexElementFormat::NormalizedShort2:
//            case VertexElementFormat::HalfVector2:
//                componentCount = 2;
//                break;
//
//            case VertexElementFormat::Vector3:
//                componentCount = 3;
//                break;
//
//            case VertexElementFormat::Vector4:
//            case VertexElementFormat::Color:
//            case VertexElementFormat::Byte4:
//            case VertexElementFormat::Short4:
//            case VertexElementFormat::NormalizedShort4:
//            case VertexElementFormat::HalfVector4:
//                componentCount = 4;
//                break;
//        }
//
//        for (int j = 0; j < componentCount; j++)
//        {
//            switch (ve.VertexElementFormat())
//            {
//                case VertexElementFormat::Single:
//                case VertexElementFormat::Vector2:
//                case VertexElementFormat::Vector3:
//                case VertexElementFormat::Color:
//                case VertexElementFormat::Vector4:
//                    std::cout << reader.ReadSingle() << "  ";
//                    break;
//
//                case VertexElementFormat::Short2:
//                case VertexElementFormat::NormalizedShort2:
//                case VertexElementFormat::HalfVector2:
//                case VertexElementFormat::Short4:
//                case VertexElementFormat::NormalizedShort4:
//                case VertexElementFormat::HalfVector4:
//                    std::cout << reader.ReadUInt16() << "  ";
//                    break;
//
//                case VertexElementFormat::Byte4:
//                    std::cout << (UInt16)reader.ReadByte() << "  ";
//                    break;
//            }
//        }
//
//        std::cout << " || ";
//    }
//
//    std::cout << " || " << std::endl;
//}
