// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/IndexBuffer.hpp>

#include <Graphics/BufferObject.hpp>

namespace SceneR
{
    namespace Graphics
    {
        IndexBuffer::IndexBuffer(gsl::not_null<GraphicsDevice*> graphicsDevice
                               , const ComponentType&           indexElementType
                               , const std::size_t&             indexCount) noexcept
            : GraphicsResource  { graphicsDevice }
            , _ibo              { nullptr }
            , _indexCount       { indexCount }
            , _indexElementType { indexElementType }
        {
            create();
        }

        void IndexBuffer::dispose()
        {
            if (_ibo != nullptr)
            {
                _ibo->dispose();
                _ibo = nullptr;
            }
        }

        std::size_t IndexBuffer::index_count() const noexcept
        {
            return _indexCount;
        }

        const ComponentType& IndexBuffer::index_element_type() const noexcept
        {
            return _indexElementType;
        }

        std::size_t IndexBuffer::element_size_in_bytes() const noexcept
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

        std::vector<std::uint8_t> IndexBuffer::get_data() const noexcept
        {
            return get_data(0, _indexCount);
        }

        std::vector<std::uint8_t> IndexBuffer::get_data(const std::size_t& startIndex
                                                      , const std::size_t& elementCount) const noexcept
        {
            Expects(_ibo != nullptr);

            auto offset = (startIndex * element_size_in_bytes());
            auto size   = (elementCount * element_size_in_bytes());

            return _ibo->get_data(offset, size);
        }

        void IndexBuffer::set_data(const gsl::span<std::uint8_t>& data) const noexcept
        {
            Expects(_ibo != nullptr);

            _ibo->set_data(_indexCount * element_size_in_bytes(), data.data());
        }

        void IndexBuffer::bind() const noexcept
        {
            Expects(_ibo != nullptr);

            _ibo->bind();
        }

        void IndexBuffer::unbind() const noexcept
        {
            Expects(_ibo != nullptr);

            _ibo->unbind();
        }

        void IndexBuffer::create() noexcept
        {
            _ibo = std::make_unique<BufferObject>(BufferTarget::ElementArraybuffer, BufferUsage::StaticDraw);
            _ibo->create();
        }
    }
}
