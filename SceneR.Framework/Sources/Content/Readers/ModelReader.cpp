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
#include <Content/Readers/ModelReader.hpp>
#include <Framework/BoundingSphere.hpp>
#include <Graphics/Effect.hpp>
#include <Graphics/IndexBuffer.hpp>
#include <Graphics/Model.hpp>
#include <Graphics/ModelBone.hpp>
#include <Graphics/ModelMesh.hpp>
#include <Graphics/ModelMeshPart.hpp>
#include <Graphics/VertexBuffer.hpp>

using namespace System;
using namespace SceneR::Content;
using namespace SceneR::Framework;
using namespace SceneR::Graphics;

ModelReader::ModelReader()
{
}

std::shared_ptr<void> ModelReader::Read(ContentReader& input)
{
    auto model     = std::make_shared<Model>();
    auto boneCount = input.ReadUInt32();

    // Read model bones
    for (UInt32 i = 0; i < boneCount; i++)
    {
        auto bone = std::make_shared<ModelBone>();

        bone->name      = this->ReadString(input);
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
            currentBone->parent = model->bones[parentBoneReference - 1];
        }

        for (UInt32 j = 0; j < childBoneCount; j++)
        {
            auto childBoneReference = this->ReadBoneReference(input, boneCount);

            if (childBoneReference > 0)
            {
                currentBone->children.push_back(model->bones[childBoneReference - 1]);
            }
        }
    }

    // Read model meshes
    auto meshCount = input.ReadUInt32();

    for (UInt32 i = 0; i< meshCount; i++)
    {
        auto modelMesh = std::make_shared<ModelMesh>();

        modelMesh->name = this->ReadString(input);

        auto parentBoneReference = this->ReadBoneReference(input, boneCount);

        if (parentBoneReference > 0)
        {
            modelMesh->parentBone = model->bones[parentBoneReference - 1];
        }

        // Mesh bounds
        modelMesh->boundingSphere = input.ReadObject<BoundingSphere>();

        // Mesh tag
        modelMesh->tag = this->ReadString(input);

        // Read mesh parts
        auto meshPartCount = input.ReadUInt32();

        for (UInt32 i = 0; i < meshPartCount; i++)
        {
            std::shared_ptr<ModelMeshPart> modelMeshPart = std::make_shared<ModelMeshPart>();

            modelMeshPart->vertexOffset   = input.ReadUInt32();
            modelMeshPart->vertexCount    = input.ReadUInt32();
            modelMeshPart->startIndex     = input.ReadUInt32();
            modelMeshPart->primitiveCount = input.ReadUInt32();
            modelMeshPart->tag            = this->ReadString(input);

            modelMesh->meshParts.push_back(modelMeshPart);

            input.ReadSharedResource(
                [=](const std::shared_ptr<void>& vertexBuffer) -> void
                {
                    modelMeshPart->vertexBuffer = std::static_pointer_cast<VertexBuffer>(vertexBuffer);
                }
            );
            input.ReadSharedResource(
                [=](const std::shared_ptr<void>& indexBuffer) -> void
                {
                    modelMeshPart->indexBuffer = std::static_pointer_cast<IndexBuffer>(indexBuffer);
                }
            );
            input.ReadSharedResource(
                [=](const std::shared_ptr<void>& effect) -> void
                {
                    modelMeshPart->effect = std::static_pointer_cast<Effect>(effect);
                }
            );
        }

        model->meshes.push_back(modelMesh);
    }

    // Model root bone
    auto rootBoneReference = this->ReadBoneReference(input, boneCount);

    if (rootBoneReference > 0)
    {
        model->root = model->bones[rootBoneReference - 1];
    }

    // Model tag
    model->tag = this->ReadString(input);

    return model;
}

UInt32 ModelReader::ReadBoneReference(ContentReader& input, const UInt16&  boneCount)
{
    if (boneCount < 255)
    {
        return input.ReadByte();
    }

    return input.ReadUInt32();
}

System::String ModelReader::ReadString(ContentReader& input)
{
    auto value = input.ReadObject<String>();

    return ((value == nullptr) ? u"" : *value);
}
