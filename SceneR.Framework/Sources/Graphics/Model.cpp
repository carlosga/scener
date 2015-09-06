// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/Model.hpp>

#include <cstddef>
#include <cstdint>
#include <cassert>

#include <Framework/Matrix.hpp>
#include <Graphics/Accessor.hpp>
#include <Graphics/BufferView.hpp>
#include <Graphics/Effect.hpp>
#include <Graphics/Material.hpp>
#include <Graphics/ModelBone.hpp>
#include <Graphics/ModelMesh.hpp>

namespace SceneR
{
    namespace Graphics
    {
        using SceneR::Framework::Matrix;
        using SceneR::Graphics::Accessor;
        using SceneR::Graphics::BufferView;
        using SceneR::Graphics::Effect;
        using SceneR::Graphics::Material;

        Model::Model()
            : _bones        ()
            , _root         ()
            , _accessors    ()
            , _buffers      ()
            , _buffer_views ()
            , _effects      ()
            , _materials    ()
            , _meshes       ()
        {
        }

        Model::~Model()
        {
        }

        void Model::dispose()
        {
            if (_buffer_views.size() > 0)
            {
                for (auto bufferView : _buffer_views)
                {
                    bufferView->dispose();
                }

                _buffer_views.clear();
            }
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

        const std::vector<std::shared_ptr<ModelMesh>>& Model::meshes() const
        {
            return _meshes;
        }

        void Model::draw(const Matrix& world, const Matrix& view, const Matrix& projection)
        {
//            auto boneTransforms = std::vector<Matrix>(_bones.size());

//            _CopyAbsoluteBoneTransformsTo(boneTransforms);

            for (const auto& mesh : _meshes)
            {
                for (auto& effect : mesh->effects())
                {
                    auto mEffect = std::dynamic_pointer_cast<IEffectMatrices>(effect);

                    if (mEffect.get() != nullptr)
                    {
                        // mEffect->world(boneTransforms[mesh->ParentBone()->Index()] * world);
                        mEffect->world(world);
                        mEffect->view(view);
                        mEffect->projection(projection);
                    }
                }

                mesh->draw();
            }
        }

        std::shared_ptr<BufferView> Model::find_buffer_view(const std::u16string& name) const
        {
            auto it = find_if(_buffer_views.begin()
                            , _buffer_views.end()
                            , [&](std::shared_ptr<BufferView> bufferView) -> bool
                              {
                                  return (bufferView->name() == name);
                              });
            return *it;
        }

        std::shared_ptr<Accessor> Model::find_accessor(const std::u16string& name) const
        {
            auto it = find_if(_accessors.begin()
                            , _accessors.end()
                            , [&](std::shared_ptr<Accessor> accessor) -> bool
                              {
                                  return (accessor->name() == name);
                              });
            return *it;
        }

        std::shared_ptr<Material> Model::find_material(const std::u16string& name) const
        {
            auto it = find_if(_materials.begin()
                            , _materials.end()
                            , [&](std::shared_ptr<Material> material) -> bool
                              {
                                  return (material->name() == name);
                              });
            return *it;
        }

        std::shared_ptr<Effect> Model::find_effect(const std::u16string &name) const
        {
            auto it = find_if(_effects.begin()
                            , _effects.end()
                            , [&](std::shared_ptr<Effect> effect) -> bool
                              {
                                  return (effect->name == name);
                              });
            return *it;
        }
    }
}
