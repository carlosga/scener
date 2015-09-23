// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/IndexBuffer.hpp>

#include <Graphics/BufferObject.hpp>

namespace SceneR
{
    namespace Graphics
    {
        IndexBuffer::IndexBuffer(Guide::not_null<GraphicsDevice*> graphicsDevice
                               , const ComponentType&             indexElementType
                               , const std::size_t&               indexCount)
            : GraphicsResource  { graphicsDevice }
            , _ibo              { nullptr }
            , _indexCount       { indexCount }
            , _indexElementType { indexElementType }
        {
        }

        void IndexBuffer::dispose()
        {
            if (_ibo.get())
            {
                _ibo->dispose();
                _ibo.release();
            }
        }

        std::size_t IndexBuffer::index_count() const
        {
            return _indexCount;
        }

        const ComponentType& IndexBuffer::index_element_type() const
        {
            return _indexElementType;
        }

        std::size_t IndexBuffer::element_size_in_bytes() const
        {
            switch (_indexElementType)
            {
            case ComponentType::Byte:
            case ComponentType::UByte:
                return sizeof(std::uint8_t);
            case ComponentType::Int16:
            case ComponentType::UInt16:
                return sizeof(std::uint16_t);
            case ComponentType::Single:
                return sizeof(float);
            }
        }

        std::vector<std::uint8_t> IndexBuffer::get_data() const
        {
            return get_data(0, _indexCount);
        }

        std::vector<std::uint8_t> IndexBuffer::get_data(const std::size_t& startIndex
                                                      , const std::size_t& elementCount) const
        {
            auto offset = (startIndex * element_size_in_bytes());
            auto size   = (elementCount * element_size_in_bytes());
            auto data   = std::vector<std::uint8_t>(size);

            _ibo->get_data(offset, size, data.data());

            return data;
        }

        void IndexBuffer::set_data(const void* data)
        {
            _ibo->set_data(_indexCount * element_size_in_bytes(), data);
        }

        void IndexBuffer::bind() const
        {
            _ibo->bind();
        }

        void IndexBuffer::unbind() const
        {
            _ibo->unbind();
        }

        void IndexBuffer::initialize()
        {
            _ibo = std::make_unique<BufferObject>(BufferTarget::ElementArraybuffer, BufferUsage::StaticDraw);
            _ibo->create();
        }
    }
}
