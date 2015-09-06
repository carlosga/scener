// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/BufferView.hpp>

#include <vector>

namespace SceneR
{
    namespace Graphics
    {
        BufferView::BufferView(const BufferTarget& target, const BufferUsage& usage)
            : _id          { 0 }
            , _target      { target }
            , _usage       { usage }
            , _byte_offset { 0 }
            , _byte_length { 0 }
            , _name        { }
        {
        }

        BufferView::~BufferView()
        {
        }

        void BufferView::dispose()
        {
            if (_id != 0)
            {
                glDeleteBuffers(1, &_id);
                _id = 0;
            }
        }

        std::uint32_t BufferView::id() const
        {
            return _id;
        }

        const BufferTarget& BufferView::target() const
        {
            return _target;
        }

        const BufferUsage& BufferView::usage() const
        {
            return _usage;
        }

        const std::u16string& BufferView::name() const
        {
            return _name;
        }

        void BufferView::activate() const
        {
            glBindBuffer(static_cast<GLenum>(_target), _id);
        }

        void BufferView::create()
        {
            glCreateBuffers(1, &_id);
        }

        void BufferView::deactivate() const
        {
            if (_id != 0)
            {
                glBindBuffer(static_cast<GLenum>(_target), 0);
            }
        }

        void BufferView::get_data(void* data) const
        {
            glGetNamedBufferSubData(_id, _byte_offset, _byte_length, data);
        }

        void BufferView::get_data(const std::size_t& offset, const std::size_t& count, void* data) const
        {
            glGetNamedBufferSubData(_id, offset, count, data);
        }

        void BufferView::set_data(const std::size_t& count, const void* data) const
        {
            glNamedBufferData(_id, count, data, static_cast<GLenum>(_usage));
        }

        void BufferView::set_data(const std::size_t& offset, const std::size_t& count, const void *data) const
        {
            glNamedBufferSubData(_id, offset, count, data);
        }

        void BufferView::invalidate() const
        {
            glInvalidateBufferData(_id);
        }

        void BufferView::invalidate(const std::size_t& offset, const std::size_t& length) const
        {
            glInvalidateBufferSubData(_id, offset, length);
        }
    }
}
