// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/model_mesh.hpp"

#include "scener/graphics/graphics_device.hpp"
#include "scener/graphics/model_mesh_part.hpp"
#include "scener/graphics/index_buffer.hpp"
#include "scener/graphics/vertex_buffer.hpp"

namespace scener::graphics
{
    const math::bounding_sphere& model_mesh::bounding_sphere() const noexcept
    {
        return _bounding_sphere;
    }

    const std::string& model_mesh::name() const noexcept
    {
        return _name;
    }

    std::vector<effect_technique*> model_mesh::effects() const noexcept
    {
        std::vector<effect_technique*> effects;

        effects.reserve(_mesh_parts.size());

        for (const auto& meshPart : _mesh_parts)
        {
            auto effect = meshPart->effect.get();

            Ensures(effect != nullptr);

            effects.push_back(effect);
        }

        return effects;
    }

    const std::vector<std::shared_ptr<model_mesh_part>>& model_mesh::mesh_parts() const noexcept
    {
        return _mesh_parts;
    }

    skeleton* model_mesh::skeleton() const noexcept
    {
        return _skeleton.get();
    }

    void model_mesh::draw() noexcept
    {
        for (const auto& meshPart : _mesh_parts)
        {
            auto device = meshPart->vertex_buffer()->device();

            if (meshPart->effect.get() != nullptr)
            {
                device->effect = meshPart->effect.get();
            }

            device->index_buffer  = meshPart->index_buffer();
            device->vertex_buffer = meshPart->vertex_buffer();

            device->draw_indexed_primitives(meshPart->primitive_type()
                                          , meshPart->vertex_offset()
                                          , 0
                                          , meshPart->vertex_count()
                                          , meshPart->start_index()
                                          , meshPart->primitive_count());
        }
    }
}
