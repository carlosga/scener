// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/BufferObject.hpp>

#include <vector>

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

        BufferObject::~BufferObject()
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

        void BufferObject::activate() const
        {
            glBindBuffer(static_cast<GLenum>(_target), _id);
        }

        void BufferObject::create()
        {
            glCreateBuffers(1, &_id);
        }

        void BufferObject::deactivate() const
        {
            if (_id != 0)
            {
                glBindBuffer(static_cast<GLenum>(_target), 0);
            }
        }

        void BufferObject::get_data(const std::size_t& offset, const std::size_t& size, void* data) const
        {
            glGetNamedBufferSubDataEXT(_id, offset, size, data);
        }

        void BufferObject::set_data(const std::size_t& size, const void* data) const
        {
            glNamedBufferDataEXT(_id, size, data, static_cast<GLenum>(_usage));
        }

        void BufferObject::set_data(const std::size_t& offset, const std::size_t& size, const void *data) const
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
