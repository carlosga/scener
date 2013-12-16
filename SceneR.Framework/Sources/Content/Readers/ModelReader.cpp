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
#include <Content/ContentType.hpp>
#include <Content/Readers/ModelReader.hpp>
#include <Framework/Matrix.hpp>
#include <Framework/RendererServiceContainer.hpp>
#include <Graphics/BasicEffect.hpp>
#include <Graphics/IGraphicsDeviceService.hpp>
#include <Graphics/IndexBuffer.hpp>
#include <Graphics/Model.hpp>
#include <Graphics/ModelBone.hpp>
#include <Graphics/ModelMesh.hpp>
#include <Graphics/ModelMeshPart.hpp>
#include <Graphics/VertexBuffer.hpp>
#include <string>
#include <vector>

using namespace System;
using namespace SceneR::Content;
using namespace SceneR::Graphics;

ModelReader::ModelReader()
{
}

const ContentType ModelReader::ContentType() const
{
    return ContentType::Model;
}

std::shared_ptr<void> ModelReader::Read(ContentReader& input)
{
    auto& gdService = input.ContentManager().ServiceProvider().GetService<IGraphicsDeviceService>();
    auto  model     = std::make_shared<Model>();
    auto  boneCount = input.ReadUInt32();

    // Read model bones
    for (UInt32 i = 0; i < boneCount; i++)
    {
        auto bone = std::make_shared<ModelBone>();

        bone->name      = input.ReadString();
        bone->transform = input.ReadMatrix();
        bone->index     = i;

        model->bones.push_back(bone);
    }

    // Read bone hierarchy
    for (UInt32 i = 0; i < boneCount; i++)
    {
        auto currentBone         = model->bones[i];
        auto parentBoneReference = this->ReadBoneReference(input, boneCount);
        auto childBoneCount      = input.ReadUInt32();

        if (parentBoneReference > 0)
        {
            currentBone->parent = model->bones[parentBoneReference];
        }

        for (UInt32 j = 0; j < childBoneCount; j++)
        {
            auto childBoneReference = this->ReadBoneReference(input, boneCount);

            if (childBoneReference > 0)
            {
                currentBone->children.push_back(model->bones[childBoneReference]);
            }
        }
    }

    // Read model meshes
    auto meshCount = input.ReadInt32();

    for (UInt32 i = 0; i< meshCount; i++)
    {
        auto modelMesh = std::make_shared<ModelMesh>();

        modelMesh->name = input.ReadString();

        auto parentBoneReference = this->ReadBoneReference(input, model->bones.size());

        if (parentBoneReference > 0)
        {
            modelMesh->parentBone = model->bones[parentBoneReference];
        }

        // TODO: Read mesh bounds
        modelMesh->tag = input.ReadString();

        // Read mesh parts
        auto meshPartCount = input.ReadUInt32();

        for (UInt32 i = 0; i < meshPartCount; i++)
        {
            auto modelMeshPart = std::make_shared<ModelMeshPart>();

            modelMeshPart->vertexOffset   = input.ReadUInt32();
            modelMeshPart->vertexCount    = input.ReadUInt32();
            modelMeshPart->startIndex     = input.ReadUInt32();
            modelMeshPart->primitiveCount = input.ReadUInt32();
            modelMeshPart->tag            = input.ReadString();
            modelMeshPart->vertexBuffer   = input.ReadObject<VertexBuffer>();
            modelMeshPart->indexBuffer    = input.ReadObject<IndexBuffer>();

            // TODO: Read the effect from the file
            auto be = std::make_shared<BasicEffect>(gdService.CurrentGraphicsDevice());

            be->EnableDefaultLighting();

            modelMeshPart->effect = be;

            modelMesh->meshParts.push_back(modelMeshPart);
        }

        model->meshes.push_back(modelMesh);
    }

    return model;
}

UInt32 ModelReader::ReadBoneReference(ContentReader& input, const UInt16&  boneCount)
{
    return input.ReadUInt32();
}
