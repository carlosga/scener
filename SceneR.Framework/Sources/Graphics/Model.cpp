// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/Model.hpp>

#include <Graphics/ModelBone.hpp>
#include <Graphics/ModelMesh.hpp>
#include <Graphics/SkinnedEffect.hpp>
#include <Graphics/SkinningData.hpp>
#include <Framework/Vector3.hpp>

using namespace System;
using namespace SceneR::Framework;
using namespace SceneR::Graphics;

Model::Model()
    : bones          ( 0 )
    , boneTransforms ( 0 )
    , meshes         ( 0 )
    , root           { nullptr }
    , tag            { u"" }
{
}

Model::~Model()
{
}

void Model::CopyAbsoluteBoneTransformsTo(std::vector<Matrix>& destinationBoneTransforms)
{
    // TODO: This isn't what it should be doing, but it's good enough for now
    destinationBoneTransforms.assign(this->boneTransforms.begin(), this->boneTransforms.end());
}

void Model::CopyBoneTransformsFrom(const std::vector<Matrix>& sourceBoneTransforms)
{
    // TODO: This isn't what it should be doing, but it's good enough for now
    this->boneTransforms = sourceBoneTransforms;
}

void Model::CopyBoneTransformsTo(std::vector<Matrix>& destinationBoneTransforms)
{
    // TODO: This isn't what it should be doing, but it's good enough for now
    destinationBoneTransforms.clear();
    destinationBoneTransforms.resize(this->bones.size());

    for (const auto& bone : this->bones)
    {
        destinationBoneTransforms.push_back(bone->Transform());
    }
}

void Model::Draw(const Matrix& world, const Matrix& view, const Matrix& projection)
{
    // Render the skinned mesh.
    for (const auto& mesh : this->meshes)
    {
        for (const auto& effect : mesh->Effects())
        {
            if (this->boneTransforms.size() > 0)
            {
                const auto sEffect = std::dynamic_pointer_cast<SkinnedEffect>(effect);

                if (sEffect != nullptr)
                {
                    sEffect->SetBoneTransforms(this->boneTransforms);

                    sEffect->SpecularColor(Vector3(0.25f, 0.25f, 0.25f));
                    sEffect->SpecularPower(16.0f);
                }
            }

            const auto mEffect = std::dynamic_pointer_cast<IEffectMatrices>(effect);

            if (mEffect != nullptr)
            {
                mEffect->World(world);
                mEffect->View(view);
                mEffect->Projection(projection);
            }
        }

        mesh->Draw();
    }
}

const std::shared_ptr<ModelBone>& Model::Root() const
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

const std::shared_ptr<SkinningData>& Model::Skinning() const
{
    return this->skinning;
}

const String& Model::Tag() const
{
    return this->tag;
}

void Model::Tag(const String& tag)
{
    this->tag = tag;
}
