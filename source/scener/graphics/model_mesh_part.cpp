// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/model_mesh_part.hpp"

namespace scener::graphics
{
    index_buffer* model_mesh_part::index_buffer() const noexcept
    {
        return _index_buffer.get();
    }

    vertex_buffer* model_mesh_part::vertex_buffer() const noexcept
    {
        return _vertex_buffer.get();
    }

    graphics::effect_technique* model_mesh_part::effect_technique() const noexcept
    {
        return _effect.get();
    }

    std::uint32_t model_mesh_part::start_index() const noexcept
    {
        return _start_index;
    }

    std::uint32_t model_mesh_part::vertex_offset() const noexcept
    {
        return _vertex_offset;
    }

    std::uint32_t model_mesh_part::vertex_count() const noexcept
    {
        return _vertex_count;
    }

    std::uint32_t model_mesh_part::primitive_count() const noexcept
    {
        return _primitive_count;
    }

    primitive_type model_mesh_part::primitive_type() const noexcept
    {
        return _primitive_type;
    }
}
