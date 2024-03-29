// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/model_mesh.hpp"

#include <algorithm>

#include "scener/graphics/graphics_device.hpp"
#include "scener/graphics/model_mesh_part.hpp"
#include "scener/graphics/model_mesh_part.hpp"
#include "scener/graphics/skeleton.hpp"

namespace scener::graphics
{
    using scener::math::matrix4;

    const math::bounding_sphere& model_mesh::bounding_sphere() const noexcept
    {
        return _bounding_sphere;
    }

    const std::string& model_mesh::name() const noexcept
    {
        return _name;
    }

    const std::vector<std::shared_ptr<model_mesh_part>>& model_mesh::mesh_parts() const noexcept
    {
        return _mesh_parts;
    }

    skeleton* model_mesh::skeleton() const noexcept
    {
        return _skeleton.get();
    }

    void model_mesh::update(const steptime& time
                          , const matrix4&  world
                          , const matrix4&  view
                          , const matrix4&  projection) noexcept
    {
        if (_skeleton != nullptr)
        {
            _skeleton->update(time.elapsed_render_time);
        }

        std::for_each(_mesh_parts.begin(), _mesh_parts.end(), [&] (const auto& part) -> void
        {
            if (_skeleton.get() != nullptr)
            {
                part->effect_technique()->bone_transforms(_skeleton->skin_transforms());
            }

            auto technique = part->effect_technique();

            technique->world(world);
            technique->view(view);
            technique->projection(projection);

            technique->update();
        });
    }

    void model_mesh::draw() noexcept
    {
        std::for_each(_mesh_parts.begin(), _mesh_parts.end(), [] (const auto& part) -> void
        {
            part->vertex_buffer()
                ->device()
                ->draw_indexed(part->vertex_offset()
                             , 0
                             , part->vertex_count()
                             , part->start_index()
                             , part->primitive_count()
                             , part->vertex_buffer()
                             , part->index_buffer()
                             , part->effect_technique());
        });
    }
}
