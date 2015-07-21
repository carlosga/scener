// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Content/Readers/ModelReader.hpp>

#include <cstdint>
#include <string>
#include <vector>

#include <Content/ContentManager.hpp>
#include <Content/ContentReader.hpp>
#include <Content/Readers/BoundingSphereReader.hpp>
#include <Framework/BoundingSphere.hpp>
#include <Graphics/Model.hpp>
#include <Graphics/ModelBone.hpp>
#include <Graphics/ModelMesh.hpp>
#include <Graphics/ModelMeshPart.hpp>
#include <Graphics/SkinningData.hpp>
#include <Graphics/Effect.hpp>
#include <Graphics/IndexBuffer.hpp>
#include <Graphics/VertexBuffer.hpp>

namespace SceneR
{
    namespace Content
    {
        using SceneR::Framework::BoundingSphere;
        using SceneR::Graphics::Effect;
        using SceneR::Graphics::IndexBuffer;
        using SceneR::Graphics::Model;
        using SceneR::Graphics::ModelBone;
        using SceneR::Graphics::ModelMesh;
        using SceneR::Graphics::ModelMeshPart;
        using SceneR::Graphics::SkinningData;
        using SceneR::Graphics::VertexBuffer;

        ModelReader::ModelReader()
        {
        }

        ModelReader::~ModelReader()
        {
        }

        std::shared_ptr<void> ModelReader::Read(ContentReader& input)
        {
            auto model     = std::make_shared<Model>();
            auto boneCount = input.ReadUInt32();

            // Read model bones
            for (std::uint32_t i = 0; i < boneCount; i++)
            {
                auto bone = std::make_shared<ModelBone>();

                bone->index     = i;
                bone->name      = this->ReadString(input);
                bone->transform = input.ReadMatrix();

                model->bones.push_back(bone);
            }

            // Read bone hierarchy
            for (std::uint32_t i = 0; i < boneCount; i++)
            {
                auto currentBone         = model->bones[i];
                auto parentBoneReference = this->ReadBoneReference(input, boneCount);
                auto childBoneCount      = input.ReadUInt32();

                if (parentBoneReference > 0)
                {
                    currentBone->parent = model->bones[parentBoneReference];
                }

                for (std::uint32_t j = 0; j < childBoneCount; j++)
                {
                    auto childBoneReference = this->ReadBoneReference(input, boneCount);

                    if (childBoneReference > 0)
                    {
                        currentBone->children.push_back(model->bones[childBoneReference]);
                    }
                }
            }

            // Read model meshes
            auto meshCount = input.ReadUInt32();

            for (std::uint32_t i = 0; i < meshCount; i++)
            {
                auto modelMesh = std::make_shared<ModelMesh>();

                modelMesh->name = this->ReadString(input);

                auto parentBoneReference = this->ReadBoneReference(input, boneCount);

                if (parentBoneReference > 0)
                {
                    modelMesh->parentBone = model->bones[parentBoneReference];
                }

                // Mesh bounds
                modelMesh->boundingSphere = *this->ReadBoundingSphere(input);

                // Mesh tag
                modelMesh->tag = this->ReadString(input);

                // Read mesh parts
                auto meshPartCount = input.ReadUInt32();

                for (std::uint32_t j = 0; j < meshPartCount; j++)
                {
                    auto modelMeshPart = std::make_shared<ModelMeshPart>();

                    modelMeshPart->vertexOffset   = input.ReadUInt32();
                    modelMeshPart->vertexCount    = input.ReadUInt32();
                    modelMeshPart->startIndex     = input.ReadUInt32();
                    modelMeshPart->primitiveCount = input.ReadUInt32();
                    modelMeshPart->tag            = this->ReadString(input);

                    modelMesh->meshParts.push_back(modelMeshPart);

                    input.ReadSharedResource(
                        [modelMeshPart](const std::shared_ptr<void>& vertexBuffer) -> void
                        {
                            modelMeshPart->vertexBuffer = std::static_pointer_cast<VertexBuffer>(vertexBuffer);
                        }
                    );
                    input.ReadSharedResource(
                        [modelMeshPart](const std::shared_ptr<void>& indexBuffer) -> void
                        {
                            modelMeshPart->indexBuffer = std::static_pointer_cast<IndexBuffer>(indexBuffer);
                        }
                    );
                    input.ReadSharedResource(
                        [modelMeshPart](const std::shared_ptr<void>& effect) -> void
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
                model->root = model->bones[rootBoneReference];
            }

            // Model tag
            // model->tag = this->ReadString(input);
            model->skinning = input.ReadObject<SkinningData>();

            return model;
        }

        std::uint32_t ModelReader::ReadBoneReference(ContentReader& input, const std::uint32_t& boneCount) const
        {
            std::uint32_t boneReference;

            if (boneCount < 255)
            {
                boneReference = input.ReadByte();
            }
            else
            {
                boneReference = input.ReadUInt32();
            }

            return ((boneReference == 0 ) ? 0 : boneReference - 1);
        }

        std::u16string ModelReader::ReadString(ContentReader& input) const
        {
            auto value = input.ReadObject<std::u16string>();

            return ((value == nullptr) ? u"" : *value);
        }

        std::shared_ptr<BoundingSphere> ModelReader::ReadBoundingSphere(ContentReader& input) const
        {
            BoundingSphereReader reader;

            return std::static_pointer_cast<BoundingSphere>(reader.Read(input));
        }
    }
}
