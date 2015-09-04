// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/Model.hpp>

#include <cstddef>
#include <cstdint>
#include <cassert>

#include <Framework/Matrix.hpp>
#include <Graphics/ModelBone.hpp>
#include <Graphics/ModelMesh.hpp>

namespace SceneR
{
    namespace Graphics
    {
        using SceneR::Framework::Matrix;

        Model::Model()
            : tag     { }
            , _bones  { }
            , _root   { nullptr }
            , _meshes { }
        {
        }

        Model::~Model()
        {
        }

        void Model::dispose()
        {
        }

        void Model::copy_absolute_bone_transforms_to(std::vector<Matrix>& destinationBoneTransforms)
        {
            assert(destinationBoneTransforms.size() == _bones.size());

            for (std::size_t boneIndex = 0; boneIndex < _bones.size(); boneIndex++)
            {
                auto bone = _bones[boneIndex];

                if (bone->parent().get() == nullptr)
                {
                    destinationBoneTransforms[boneIndex] = bone->transform();
                }
                else
                {
                    std::uint32_t parentBoneIndex = bone->parent()->index();

                    destinationBoneTransforms[boneIndex] = bone->transform() * destinationBoneTransforms[parentBoneIndex];
                }
            }
        }

        void Model::copy_bone_transforms_from(const std::vector<Matrix>& sourceBoneTransforms)
        {
            assert(sourceBoneTransforms.size() == _bones.size());

            for (std::size_t i = 0; i < sourceBoneTransforms.size(); i++)
            {
                _bones[i]->transform(sourceBoneTransforms[i]);
            }
        }

        void Model::copy_bone_transforms_to(std::vector<Matrix>& destinationBoneTransforms)
        {
            assert(destinationBoneTransforms.size() == _bones.size());

            for (std::size_t i = 0; i < _bones.size(); i++)
            {
                destinationBoneTransforms[i] = _bones[i]->transform();
            }
        }

        const std::shared_ptr<ModelBone>& Model::root() const
        {
            return _root;
        }

        const std::vector<std::shared_ptr<ModelBone>>& Model::bones() const
        {
            return _bones;
        }

        const std::map<std::string, std::shared_ptr<ModelMesh>>& Model::meshes() const
        {
            return _meshes;
        }

        void Model::draw(const Matrix& world, const Matrix& view, const Matrix& projection)
        {
//            auto boneTransforms = std::vector<Matrix>(_bones.size());

//            _CopyAbsoluteBoneTransformsTo(boneTransforms);

//            for (auto& mesh : _meshes)
//            {
//                for (auto& effect : mesh->Effects())
//                {
//                    auto mEffect = std::dynamic_pointer_cast<IEffectMatrices>(effect);

//                    if (mEffect.get() != nullptr)
//                    {
//                        mEffect->World(boneTransforms[mesh->ParentBone()->Index()] * world);
//                        mEffect->View(view);
//                        mEffect->Projection(projection);
//                    }
//                }

//                mesh->draw();
//            }
        }
    }
}
