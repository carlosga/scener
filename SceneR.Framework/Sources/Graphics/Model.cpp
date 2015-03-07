// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/Model.hpp>

#include <cassert>

#include <Framework/Vector3.hpp>
#include <Graphics/ModelBone.hpp>
#include <Graphics/ModelMesh.hpp>
#include <Graphics/SkinnedEffect.hpp>

using namespace System;
using namespace SceneR::Framework;
using namespace SceneR::Graphics;

Model::Model()
    : bones  ( 0 )
    , meshes ( 0 )
    , root   { nullptr }
    , tag    { u"" }
{
}

Model::~Model()
{
}

void Model::Dispose()
{
}

void Model::CopyAbsoluteBoneTransformsTo(std::vector<Matrix>& destinationBoneTransforms)
{
    assert(destinationBoneTransforms.size() == this->bones.size());

    for (UInt32 boneIndex = 0; boneIndex < this->bones.size(); boneIndex++)
    {
        auto bone = this->bones[boneIndex];

        if (bone->Parent().get() == nullptr)
        {
            destinationBoneTransforms[boneIndex] = bone->Transform();
        }
        else
        {
            UInt32 parentBoneIndex = bone->Parent()->Index();

            destinationBoneTransforms[boneIndex] = bone->Transform() * destinationBoneTransforms[parentBoneIndex];
        }
    }
}

void Model::CopyBoneTransformsFrom(const std::vector<Matrix>& sourceBoneTransforms)
{
    assert(sourceBoneTransforms.size() == this->bones.size());

    for (UInt32 i = 0; i < sourceBoneTransforms.size(); i++)
    {
        this->bones[i]->Transform(sourceBoneTransforms[i]);
    }
}

void Model::CopyBoneTransformsTo(std::vector<Matrix>& destinationBoneTransforms)
{
    assert(destinationBoneTransforms.size() == this->bones.size());

    for (UInt32 i = 0; i < this->bones.size(); i++)
    {
        destinationBoneTransforms[i] = this->bones[i]->Transform();
    }
}

void Model::Draw(const Matrix& world, const Matrix& view, const Matrix& projection)
{
    auto boneTransforms = std::vector<Matrix>(this->bones.size());

    this->CopyAbsoluteBoneTransformsTo(boneTransforms);

    for (auto& mesh : this->meshes)
    {
        for (auto& effect : mesh->Effects())
        {
            auto mEffect = std::dynamic_pointer_cast<IEffectMatrices>(effect);

            if (mEffect.get() != nullptr)
            {
                mEffect->World(boneTransforms[mesh->ParentBone()->Index()] * world);
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
