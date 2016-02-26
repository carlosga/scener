// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/ModelMeshPart.hpp"

#include "scener/graphics/EffectTechnique.hpp"
#include "scener/graphics/IndexBuffer.hpp"
#include "scener/graphics/VertexBuffer.hpp"

namespace scener { namespace graphics {

IndexBuffer* ModelMeshPart::index_buffer() const noexcept
{
    return _index_buffer.get();
}

VertexBuffer* ModelMeshPart::vertex_buffer() const noexcept
{
    return _vertex_buffer.get();
}

std::size_t ModelMeshPart::start_index() const noexcept
{
    return _start_index;
}

std::size_t ModelMeshPart::vertex_offset() const noexcept
{
    return _vertex_offset;
}

std::size_t ModelMeshPart::vertex_count() const noexcept
{
    return _vertex_count;
}

std::size_t ModelMeshPart::primitive_count() const noexcept
{
    return _primitive_count;
}

PrimitiveType ModelMeshPart::primitive_type() const noexcept
{
    return _primitive_type;
}

}}
