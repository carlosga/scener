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

#include <Graphics/GraphicsDevice.hpp>
#include <Graphics/ModelMesh.hpp>
#include <Graphics/PrimitiveType.hpp>

using namespace SceneR::Graphics;

ModelMesh::ModelMesh()
    : meshParts(0), name(), parentBone(nullptr), tag()
{
}

ModelMesh::~ModelMesh()
{
}

void ModelMesh::Draw()
{
    for (auto& meshPart : this->meshParts)
    {
        auto graphicsDevice = meshPart->GetVertexBuffer()->GetGraphicsDevice();

        graphicsDevice.SetEffect(meshPart->GetEffect());
        graphicsDevice.SetVertexBuffer(meshPart->GetVertexBuffer());
        graphicsDevice.SetIndexBuffer(meshPart->GetIndexBuffer());

        graphicsDevice.DrawIndexedPrimitives(PrimitiveType::TriangleList,
                                             0,
                                             0,
                                             meshPart->GetVertexCount(),
                                             meshPart->GetStartIndex(),
                                             meshPart->GetPrimitiveCount());
    }
}

const std::vector<std::shared_ptr<Effect>> ModelMesh::GetEffects()
{
    std::vector<std::shared_ptr<Effect>> effects(0);

    for (auto &meshPart : this->meshParts)
    {
        if (meshPart->GetEffect() != nullptr)
        {
            effects.push_back(meshPart->GetEffect());
        }
    }

    return effects;
}

const std::vector<std::shared_ptr<ModelMeshPart>>& ModelMesh::MeshParts() const
{
    return this->meshParts;
}

const std::wstring& ModelMesh::GetName() const
{
    return this->name;
}

void ModelMesh::SetName(const std::wstring& name)
{
    this->name = name;
}

std::shared_ptr<ModelBone> ModelMesh::ParentBone() const
{
    return this->parentBone;
}

const std::wstring& ModelMesh::GetTag() const
{
    return this->tag;
}

void ModelMesh::SetTag(const std::wstring& tag)
{
    this->tag = tag;
}
