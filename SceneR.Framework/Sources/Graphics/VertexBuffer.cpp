// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/VertexBuffer.hpp>

namespace SceneR
{
    namespace Graphics
    {
        VertexBuffer::VertexBuffer(Guide::not_null<GraphicsDevice*>   graphicsDevice
                                 , const std::size_t&                 vertexCount
                                 , std::unique_ptr<VertexDeclaration> vertexDeclaration)
            : GraphicsResource    { graphicsDevice }
            , _binding_index      { 0 }
            , _vertex_count       { vertexCount }
            , _vertex_declaration { std::move(vertexDeclaration) }
            , _vao                { nullptr }
            , _vbo                { nullptr }
        {
        }

        void VertexBuffer::dispose()
        {
            if (_vao.get())
            {
                _vao->dispose();
                _vao.release();
            }
            if (_vbo.get())
            {
                _vbo->dispose();
                _vbo.release();
            }
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

            _vbo->get_data(offset, size, data.data());

            return data;
        }

        void VertexBuffer::set_data(const void* data)
        {
            _vbo->set_data(_vertex_count * _vertex_declaration->vertex_stride(), data);
        }

        VertexDeclaration* VertexBuffer::vertex_declaration() const
        {
            return _vertex_declaration.get();
        }

        void VertexBuffer::bind()
        {
            _vao->bind();
        }

        void VertexBuffer::unbind()
        {
            _vao->unbind();
        }

        void VertexBuffer::initialize()
        {
            _vao = std::make_unique<VertexArrayObject>();
            _vbo = std::make_unique<BufferObject>(BufferTarget::ArrayBuffer, BufferUsage::StaticDraw);

            _vao->create();
            _vao->bind();
            _vbo->create();

            _vertex_declaration->declare(_vao->id(), _binding_index);

            glVertexArrayVertexBuffer(_vao->id(), _binding_index, _vbo->id(), 0, _vertex_declaration->vertex_stride());

            _vao->unbind();
        }
    }
}
