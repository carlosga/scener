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

#include <Framework/Vector3.hpp>
#include <Graphics/GraphicsDevice.hpp>
#include <Graphics/ModelMesh.hpp>
#include <Graphics/PrimitiveType.hpp>
#include <string>

using namespace System;
using namespace SceneR::Framework;
using namespace SceneR::Graphics;

ModelMesh::ModelMesh()
    : boundingSphere(Vector3::Zero, 0.0f)
    , meshParts(0)
    , name()
    , parentBone(nullptr)
    , tag()
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

        if (meshPart->Effect() != nullptr)
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

const std::shared_ptr<ModelBone>& ModelMesh::ParentBone() const
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
