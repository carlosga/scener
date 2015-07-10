// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
//-----------------------------------------------------------------------------
// Ported from a Microsoft XNA Community Game Platform example
//-----------------------------------------------------------------------------
// Microsoft XNA Community Game Platform
// Copyright (C) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------

#include <Graphics/AnimatedModel.hpp>

#include <Framework/RenderTime.hpp>
#include <Graphics/SkinningData.hpp>
#include <Graphics/Model.hpp>
#include <Graphics/ModelMesh.hpp>
#include <Graphics/SkinnedEffect.hpp>

namespace SceneR
{
    namespace Graphics
    {
        using SceneR::Framework::RenderTime;
        using SceneR::Framework::Matrix;

        AnimatedModel::AnimatedModel(const std::shared_ptr<Model>& model)
            : model        { model }
            , skinningData { model->Skinning() }
            , player       { model->Skinning() }
        {
        }

        AnimatedModel::~AnimatedModel()
        {
        }

        void AnimatedModel::Play(const std::u16string& clipName)
        {
            this->player.StartClip(this->skinningData->AnimationClips(clipName));
        }

        void AnimatedModel::PlayFirstClip()
        {
            this->player.StartClip(this->skinningData->AnimationClips().begin()->second);
        }

        void AnimatedModel::Update(const RenderTime& renderTime)
        {
            this->player.Update(renderTime.ElapsedRenderTime(), true, Matrix::Identity);
        }

        void AnimatedModel::Draw(const Matrix& world, const Matrix& view, const Matrix& projection)
        {
            auto& bones = this->player.GetSkinTransforms();

            // Render the skinned mesh.
            for (auto& mesh : this->model->Meshes())
            {
                for (auto& effect : mesh->Effects())
                {
                    auto sEffect = std::dynamic_pointer_cast<SkinnedEffect>(effect);

                    sEffect->SetBoneTransforms(bones);
                    sEffect->World(world);
                    sEffect->View(view);
                    sEffect->Projection(projection);
                }

                mesh->Draw();
            }
        }
    }
}
