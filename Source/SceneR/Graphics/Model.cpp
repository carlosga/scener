// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SceneR/Graphics/Model.hpp"

#include "SceneR/Graphics/EffectTechnique.hpp"
#include "SceneR/Graphics/ModelMesh.hpp"
#include "SceneR/Graphics/Skeleton.hpp"
#include "SceneR/Graphics/StepTime.hpp"

namespace SceneR { namespace Graphics {

using SceneR::Math::Matrix;

Model::Model() noexcept
    : _meshes (0)
    , _name   ()
{
}

const std::string& Model::name() const noexcept
{
    return _name;
}

const std::vector<std::shared_ptr<ModelMesh>>& Model::meshes() const noexcept
{
    return _meshes;
}

void Model::update(const StepTime& elapsedtime) noexcept
{
    for (const auto& mesh : _meshes)
    {
        if (mesh->skeleton() != nullptr)
        {
            mesh->skeleton()->update(elapsedtime.elapsed_render_time);
        }
    }
}

void Model::draw(const Matrix& world, const Matrix& view, const Matrix& projection) noexcept
{
    for (const auto& mesh : _meshes)
    {
        for (const auto& effect : mesh->effects())
        {
            if (mesh->skeleton() != nullptr)
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

}}
