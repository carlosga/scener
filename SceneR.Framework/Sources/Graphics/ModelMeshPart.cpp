// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/ModelMeshPart.hpp>

#include <Graphics/Effect.hpp>
#include <Graphics/IndexBuffer.hpp>
#include <Graphics/VertexBuffer.hpp>

namespace SceneR
{
    namespace Graphics
    {
        ModelMeshPart::ModelMeshPart()
            : effect           { nullptr }
            , _index_buffer    { nullptr }
            , _vertex_buffer   { nullptr }
            , _start_index     { 0 }
            , _vertex_offset   { 0 }
            , _vertex_count    { 0 }
            , _primitive_count { 0 }
            , _primitive_type  { PrimitiveType::TriangleList }
        {
        }

        ModelMeshPart::~ModelMeshPart()
        {
        }

        IndexBuffer* ModelMeshPart::index_buffer() const
        {
            return _index_buffer.get();
        }

        VertexBuffer* ModelMeshPart::vertex_buffer() const
        {
            return _vertex_buffer.get();
        }

        std::size_t ModelMeshPart::start_index() const
        {
            return _start_index;
        }

        std::size_t ModelMeshPart::vertex_offset() const
        {
            return _vertex_offset;
        }

        std::size_t ModelMeshPart::vertex_count() const
        {
            return _vertex_count;
        }

        std::size_t ModelMeshPart::primitive_count() const
        {
            return _primitive_count;
        }

        const PrimitiveType& ModelMeshPart::primitive_type() const
        {
            return _primitive_type;
        }
    }
}
