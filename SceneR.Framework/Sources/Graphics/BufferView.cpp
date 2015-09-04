// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/BufferView.hpp>

#include <vector>

namespace SceneR
{
    namespace Graphics
    {
        BufferView::BufferView(const BufferTarget& target, const BufferUsage& usage)
            : id     { 0 }
            , target { target }
            , usage  { usage }
        {
            this->Create();
        }

        BufferView::~BufferView()
        {
        }

        void BufferView::Dispose()
        {
            if (this->id != 0)
            {
                glDeleteBuffers(1, &this->id);
                this->id = 0;
            }
        }

        std::uint32_t BufferView::Id() const
        {
            return this->id;
        }

        const BufferTarget&BufferView::Target() const
        {
            return this->target;
        }

        const BufferUsage&BufferView::Usage() const
        {
            return this->usage;
        }

        void BufferView::Activate() const
        {
            glBindBuffer(static_cast<GLenum>(this->target), this->id);
        }

        void BufferView::Deactivate() const
        {
            if (this->id != 0)
            {
                glBindBuffer(static_cast<GLenum>(this->target), 0);
            }
        }

        void BufferView::GetData(const std::size_t& offset, const std::size_t& size, void* data) const
        {
            glGetNamedBufferSubData(this->id, offset, size, data);
        }

        void BufferView::BufferData(const std::size_t& size, const void* data) const
        {
            glNamedBufferData(this->id, size, data, static_cast<GLenum>(this->usage));
        }

        void BufferView::BufferData(const std::size_t& offset, const std::size_t& size, const void *data) const
        {
            glNamedBufferSubData(this->id, offset, size, data);
        }

        void BufferView::Invalidate() const
        {
            glInvalidateBufferData(this->id);
        }

        void BufferView::Invalidate(const std::size_t& offset, const std::size_t& length) const
        {
            glInvalidateBufferSubData(this->id, offset, length);
        }

        void BufferView::Create()
        {
            glCreateBuffers(1, &this->id);
        }
    }
}
