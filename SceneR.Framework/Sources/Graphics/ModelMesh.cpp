// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/ModelMesh.hpp>

#include <Framework/Vector3.hpp>
#include <Graphics/GraphicsDevice.hpp>
#include <Graphics/ModelMeshPart.hpp>
#include <Graphics/ModelBone.hpp>
#include <Graphics/VertexBuffer.hpp>

namespace SceneR
{
    namespace Graphics
    {
        using SceneR::Framework::BoundingSphere;
        using SceneR::Framework::Vector3;

        ModelMesh::ModelMesh()
            : boundingSphere { Vector3::Zero, 0.0f }
            , meshParts      ( 0 )
            , name           { u"" }
            , parentBone     { nullptr }
            , tag            { u"" }
        {
        }

        ModelMesh::~ModelMesh()
        {
        }

        const SceneR::Framework::BoundingSphere& ModelMesh::BoundingSphere() const
        {
            return this->boundingSphere;
        }

        void ModelMesh::Draw()
        {
            for (const auto& meshPart : this->meshParts)
            {
                auto& graphicsDevice = meshPart->VertexBuffer()->CurrentGraphicsDevice();

                if (meshPart->Effect().get() != nullptr)
                {
                    graphicsDevice.Effect(meshPart->Effect());
                }

                graphicsDevice.VertexBuffer(meshPart->VertexBuffer());
                graphicsDevice.IndexBuffer(meshPart->IndexBuffer());

                graphicsDevice.DrawIndexedPrimitives(PrimitiveType::TriangleList
                                                   , meshPart->VertexOffset()
                                                   , 0
                                                   , meshPart->VertexCount()
                                                   , meshPart->StartIndex()
                                                   , meshPart->PrimitiveCount());
            }
        }

        std::vector<std::shared_ptr<Effect>> ModelMesh::Effects() const
        {
            auto effects = std::vector<std::shared_ptr<Effect>>(0);

            for (const auto& meshPart : this->meshParts)
            {
                if (meshPart->Effect().get() != nullptr)
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

        const std::u16string& ModelMesh::Name() const
        {
            return this->name;
        }

        void ModelMesh::Name(const std::u16string& name)
        {
            this->name = name;
        }

        const std::shared_ptr<ModelBone>& ModelMesh::ParentBone() const
        {
            return this->parentBone;
        }

        const std::u16string& ModelMesh::Tag() const
        {
            return this->tag;
        }

        void ModelMesh::Tag(const std::u16string& tag)
        {
            this->tag = tag;
        }
    }
}
