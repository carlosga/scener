// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/IndexBuffer.hpp>

namespace SceneR
{
    namespace Graphics
    {
        IndexBuffer::IndexBuffer(GraphicsDevice&                   graphicsDevice
                               , const Graphics::IndexElementSize& indexElementSize
                               , const std::size_t&                indexCount)
            : GraphicsResource  { graphicsDevice }
            , _ibo              { BufferTarget::ElementArraybuffer, BufferUsage::StaticDraw }
            , _indexCount       { indexCount }
            , _indexElementSize { indexElementSize }
        {
        }

        IndexBuffer::~IndexBuffer()
        {
        }

        void IndexBuffer::dispose()
        {
            _ibo.dispose();
        }

        std::size_t IndexBuffer::index_count() const
        {
            return _indexCount;
        }

        const IndexElementSize& IndexBuffer::index_element_size() const
        {
            return _indexElementSize;
        }

        std::vector<std::uint8_t> IndexBuffer::get_data() const
        {
            return get_data(0, _indexCount);
        }

        std::vector<std::uint8_t> IndexBuffer::get_data(const std::size_t& startIndex, const std::size_t& elementCount) const
        {
            auto offset = (startIndex * get_element_size_in_bytes());
            auto size   = (elementCount * get_element_size_in_bytes());
            auto data   = std::vector<std::uint8_t>(size);

            _ibo.get_data(offset, size, data.data());

            return data;
        }

        void IndexBuffer::set_data(const void* data)
        {
            _ibo.buffer_data(_indexCount * get_element_size_in_bytes(), data);
        }

        void IndexBuffer::activate() const
        {
            _ibo.activate();
        }

        void IndexBuffer::deactivate() const
        {
            _ibo.deactivate();
        }

        std::size_t IndexBuffer::get_element_size_in_bytes() const
        {
            return ((_indexElementSize == IndexElementSize::SixteenBits) ? sizeof(std::uint16_t) : sizeof(std::uint32_t));
        }
    }
}
