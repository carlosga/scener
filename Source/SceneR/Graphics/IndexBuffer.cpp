// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SceneR/Graphics/IndexBuffer.hpp"

#include "SceneR/Graphics/OpenGL/BufferTarget.hpp"
#include "SceneR/Graphics/OpenGL/BufferUsage.hpp"

namespace scener { namespace graphics {

using scener::graphics::opengl::Buffer;
using scener::graphics::opengl::BufferTarget;
using scener::graphics::opengl::BufferUsage;

IndexBuffer::IndexBuffer(gsl::not_null<GraphicsDevice*> graphicsDevice
                       , ComponentType                  indexElementType
                       , std::size_t                    indexCount) noexcept
    : GraphicsResource  { graphicsDevice }
    , _buffer           { BufferTarget::element_array_buffer, BufferUsage::static_draw }
    , _indexCount       { indexCount }
    , _indexElementType { indexElementType }
{
}

std::size_t IndexBuffer::index_count() const noexcept
{
    return _indexCount;
}

ComponentType IndexBuffer::index_element_type() const noexcept
{
    return _indexElementType;
}

std::size_t IndexBuffer::element_size_in_bytes() const noexcept
{
    switch (_indexElementType)
    {
    case ComponentType::byte:
    case ComponentType::ubyte:
        return sizeof(std::uint8_t);
    case ComponentType::int16:
    case ComponentType::uint16:
        return sizeof(std::uint16_t);
    case ComponentType::single:
        return sizeof(float);
    }
}

std::vector<std::uint8_t> IndexBuffer::get_data() const noexcept
{
    return get_data(0, _indexCount);
}

std::vector<std::uint8_t> IndexBuffer::get_data(std::size_t startIndex, std::size_t elementCount) const noexcept
{
    auto offset = (startIndex * element_size_in_bytes());
    auto size   = (elementCount * element_size_in_bytes());

    return _buffer.get_data(offset, size);
}

void IndexBuffer::set_data(const gsl::span<const std::uint8_t>& data) const noexcept
{
    _buffer.set_data(_indexCount * element_size_in_bytes(), data.data());
}

void IndexBuffer::bind() const noexcept
{
    _buffer.bind();
}

void IndexBuffer::unbind() const noexcept
{
    _buffer.unbind();
}

}}
