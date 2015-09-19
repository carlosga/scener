// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/Model.hpp>

#include <cassert>

#include <Framework/Matrix.hpp>
#include <Graphics/EffectTechnique.hpp>
#include <Graphics/ModelBone.hpp>
#include <Graphics/ModelMesh.hpp>
#include <Graphics/ModelSkin.hpp>

namespace SceneR
{
    namespace Graphics
    {
        using SceneR::Framework::Matrix;

        Model::Model()
            : _name   ()
            , _bones  (0)
            , _root   ()
            , _meshes (0)
        {
        }

        Model::~Model()
        {
        }

        void Model::dispose()
        {
        }

        const std::string Model::name() const
        {
            return _name;
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
            auto boneTransforms = std::vector<Matrix>();

            for (const auto mesh : _meshes)
            {
                for (const auto effect : mesh->effects())
                {
                    //effect->world(boneTransforms[mesh->ParentBone()->Index()] * world);
                    effect->world(world);
                    effect->view(view);
                    effect->projection(projection);
                }

                mesh->draw();
            }
        }
    }
}
