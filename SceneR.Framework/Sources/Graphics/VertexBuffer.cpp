// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/VertexBuffer.hpp>

#include <Graphics/VertexDeclaration.hpp>

namespace SceneR
{
    namespace Graphics
    {
        VertexBuffer::VertexBuffer(GraphicsDevice&                                             graphicsDevice
                                 , const std::size_t&                                          vertexCount
                                 , const std::shared_ptr<SceneR::Graphics::VertexDeclaration>& vertexDeclaration)
            : GraphicsResource    { graphicsDevice }
            , _binding_index      { 0 }
            , _vertex_declaration { vertexDeclaration }
            , _vertex_count       { vertexCount }
            , _vao                { }
            , _vbo                { BufferTarget::ArrayBuffer, BufferUsage::StaticDraw }
        {
            _vertex_declaration->declare(_vao.id(), _binding_index);

            auto vertexStride = static_cast<GLsizei>(_vertex_declaration->vertex_stride());

            glVertexArrayVertexBuffer(_vao.id(), _binding_index, _vbo.id(), 0, vertexStride);
        }

        VertexBuffer::~VertexBuffer()
        {
        }

        void VertexBuffer::dispose()
        {
            _vao.dispose();
            _vbo.dispose();
        }

        std::size_t VertexBuffer::vertex_count() const
        {
            return _vertex_count;
        }

        std::vector<std::uint8_t> VertexBuffer::get_data() const
        {
            return get_data(0, _vertex_count);
        }

        std::vector<std::uint8_t> VertexBuffer::get_data(const std::size_t& startIndex
                                                       , const std::size_t& elementCount) const
        {
            auto offset = (startIndex * _vertex_declaration->vertex_stride());
            auto size   = (elementCount * _vertex_declaration->vertex_stride());
            auto data   = std::vector<std::uint8_t>(size, 0);

            _vbo.get_data(offset, size, data.data());

            return data;
        }

        void VertexBuffer::set_data(const void* data)
        {
            _vbo.set_data(_vertex_count * _vertex_declaration->vertex_stride(), data);
        }

        std::shared_ptr<SceneR::Graphics::VertexDeclaration> VertexBuffer::vertex_declaration() const
        {
            return _vertex_declaration;
        }

        void VertexBuffer::activate()
        {
            _vao.activate();
        }

        void VertexBuffer::deactivate()
        {
            _vao.deactivate();
        }
    }
}
