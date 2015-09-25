// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/BufferObject.hpp>

namespace SceneR
{
    namespace Graphics
    {
        BufferObject::BufferObject(const BufferTarget& target, const BufferUsage& usage)
            : _id     { 0 }
            , _target { target }
            , _usage  { usage }
        {
        }

        void BufferObject::dispose()
        {
            if (_id != 0)
            {
                glDeleteBuffers(1, &_id);
                _id = 0;
            }
        }

        std::uint32_t BufferObject::id() const
        {
            return _id;
        }

        const BufferTarget& BufferObject::target() const
        {
            return _target;
        }

        const BufferUsage& BufferObject::usage() const
        {
            return _usage;
        }

        void BufferObject::bind() const
        {
            glBindBuffer(static_cast<GLenum>(_target), _id);
        }

        void BufferObject::create()
        {
            glCreateBuffers(1, &_id);
        }

        void BufferObject::unbind() const
        {
            if (_id != 0)
            {
                glBindBuffer(static_cast<GLenum>(_target), 0);
            }
        }

        std::vector<std::uint8_t> BufferObject::get_data(const std::size_t& offset, const std::size_t& size) const
        {
            auto data = std::vector<std::uint8_t>(size, 0);

            glGetNamedBufferSubDataEXT(_id, offset, size, data.data());

            return data;
        }

        void BufferObject::set_data(const std::size_t& size, const void* data) const
        {
            glNamedBufferDataEXT(_id, size, data, static_cast<GLenum>(_usage));
        }

        void BufferObject::set_data(const std::size_t& offset, const std::size_t& size, const void* data) const
        {
            glNamedBufferSubDataEXT(_id, offset, size, data);
        }

        void BufferObject::invalidate() const
        {
            glInvalidateBufferData(_id);
        }

        void BufferObject::invalidate(const std::size_t& offset, const std::size_t& length) const
        {
            glInvalidateBufferSubData(_id, offset, length);
        }
    }
}
