// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/model_mesh_part.hpp"

#include "scener/graphics/effect_technique.hpp"
#include "scener/graphics/index_buffer.hpp"
#include "scener/graphics/vertex_buffer.hpp"

namespace scener { namespace graphics {

index_buffer* model_mesh_part::index_buffer() const noexcept
{
    return _index_buffer.get();
}

vertex_buffer* model_mesh_part::vertex_buffer() const noexcept
{
    return _vertex_buffer.get();
}

std::size_t model_mesh_part::start_index() const noexcept
{
    return _start_index;
}

std::size_t model_mesh_part::vertex_offset() const noexcept
{
    return _vertex_offset;
}

std::size_t model_mesh_part::vertex_count() const noexcept
{
    return _vertex_count;
}

std::size_t model_mesh_part::primitive_count() const noexcept
{
    return _primitive_count;
}

primitive_type model_mesh_part::primitive_type() const noexcept
{
    return _primitive_type;
}

}}
