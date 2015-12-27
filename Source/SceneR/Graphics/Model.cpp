// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "Model.hpp"

#include "EffectTechnique.hpp"
#include "ModelMesh.hpp"
#include "Skeleton.hpp"
#include "StepTime.hpp"

namespace SceneR
{
    namespace Graphics
    {
        using SceneR::Math::Matrix;

        Model::Model() noexcept
            : _name   ()
            , _meshes (0)
        {
        }

        void Model::dispose()
        {
        }

        const std::string Model::name() const noexcept
        {
            return _name;
        }

        const std::vector<std::shared_ptr<ModelMesh>>& Model::meshes() const noexcept
        {
            return _meshes;
        }

        void Model::update(const StepTime& elapsedtime) noexcept
        {
            for (const auto mesh : _meshes)
            {
                if (mesh->skeleton())
                {
                    mesh->skeleton()->update(elapsedtime.elapsed_render_time, true, Matrix::identity);
                }
            }
        }

        void Model::draw(const Matrix& world, const Matrix& view, const Matrix& projection) noexcept
        {
            for (const auto mesh : _meshes)
            {
                for (const auto effect : mesh->effects())
                {
                    if (mesh->skeleton())
                    {
                        effect->bone_transforms(mesh->skeleton()->skin_transforms());
                    }

                    effect->world(world);
                    effect->view(view);
                    effect->projection(projection);
                }

                mesh->draw();
            }
        }
    }
}
