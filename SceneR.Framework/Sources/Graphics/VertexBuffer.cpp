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
            : GraphicsResource  { graphicsDevice }
            , bindingIndex      { 0 }
            , vertexDeclaration { vertexDeclaration }
            , vertexCount       { vertexCount }
            , vao               { }
            , vbo               { BufferTarget::ArrayBuffer, BufferUsage::StaticDraw }
        {
            this->vertexDeclaration->Declare(this->vao.Id(), this->bindingIndex);

            glVertexArrayVertexBuffer(this->vao.Id()
                                    , this->bindingIndex
                                    , this->vbo.id()
                                    , 0
                                    , static_cast<GLsizei>(this->vertexDeclaration->VertexStride()));
        }

        VertexBuffer::~VertexBuffer()
        {
        }

        void VertexBuffer::dispose()
        {
            this->vao.dispose();
            this->vbo.dispose();
        }

        std::size_t VertexBuffer::VertexCount() const
        {
            return this->vertexCount;
        }

        std::vector<std::uint8_t> VertexBuffer::GetData() const
        {
            return this->GetData(0, this->vertexCount);
        }

        std::vector<std::uint8_t> VertexBuffer::GetData(const std::size_t& startIndex
                                                      , const std::size_t& elementCount) const
        {
            auto offset = (startIndex * this->vertexDeclaration->VertexStride());
            auto size   = (elementCount * this->vertexDeclaration->VertexStride());
            auto data   = std::vector<std::uint8_t>(size, 0);

            this->vbo.get_data(offset, size, data.data());

            return data;
        }

        void VertexBuffer::SetData(const void* data)
        {
            this->vbo.buffer_data(this->vertexCount * this->vertexDeclaration->VertexStride(), data);
        }

        std::shared_ptr<SceneR::Graphics::VertexDeclaration> VertexBuffer::VertexDeclaration() const
        {
            return this->vertexDeclaration;
        }

        void VertexBuffer::Activate()
        {
            this->vao.Activate();
        }

        void VertexBuffer::Deactivate()
        {
            this->vao.Deactivate();
        }
    }
}
