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

#include "Graphics/IEffectMatrices.hpp"
#include "Graphics/Model.hpp"

using namespace SceneR::Core;
using namespace SceneR::Graphics;

Model::Model()
    : bones(0),
      meshes(0),
      root(nullptr),
      tag()
{
}

void Model::Draw(const Matrix& world,
                 const Matrix& view,
                 const Matrix& projection)
{
    for (auto &mesh : this->meshes)
    {
        for (auto &effect : mesh->GetEffects())
        {
            std::shared_ptr<IEffectMatrices> mEffect = std::dynamic_pointer_cast<IEffectMatrices>(effect);

            if (mEffect != nullptr)
            {
                mEffect->SetWorld(world);
                mEffect->SetView(view);
                mEffect->SetProjection(projection);
            }
        }

        mesh->Draw();
    }
}

const std::shared_ptr<ModelBone> Model::Root() const
{
    return this->root;
}

const std::vector<std::shared_ptr<ModelBone>>& Model::Bones() const
{
    return this->bones;
}

const std::vector<std::shared_ptr<ModelMesh>>& Model::Meshes() const
{
    return this->meshes;
}

const std::wstring& Model::GetTag() const
{
    return this->tag;
}

void Model::SetTag(const std::wstring& tag)
{
    this->tag = tag;
}
