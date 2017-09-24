// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/model.hpp"

#include <algorithm>

namespace scener::graphics
{
    using scener::math::matrix4;

    model::model() noexcept
        : _meshes { }
        , _name   { }
    {
    }

    const std::string& model::name() const noexcept
    {
        return _name;
    }

    const std::vector<std::shared_ptr<model_mesh>>& model::meshes() const noexcept
    {
        return _meshes;
    }

    void model::update(const steptime& time) noexcept
    {
        std::for_each(_meshes.begin(), _meshes.end(), [&time] (auto& mesh) -> void { mesh->update(time); });
    }

    void model::draw(const matrix4& world, const matrix4& view, const matrix4& projection) noexcept
    {
        std::for_each(_meshes.begin(), _meshes.end(), [&] (auto& mesh) -> void { mesh->draw(world, view, projection); });
    }
}
