// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SceneR/Graphics/UniformBufferObject.hpp"

#include <gsl.h>

#include "SceneR/Graphics/BufferObject.hpp"
#include "SceneR/Graphics/OpenGL/Platform.hpp"

namespace SceneR
{
    namespace Graphics
    {
        UniformBufferObject::UniformBufferObject(const std::string& name, const std::uint32_t& programId) noexcept
            : _name          { name }
            , _program_id    { programId }
            , _index         { 0 }
            , _binding_point { 0 }
            , _size          { 0 }
            , _buffer_object { std::make_unique<BufferObject>(BufferTarget::UniformBuffer, BufferUsage::DynamicDraw) }
        {
        }

        void UniformBufferObject::dispose()
        {
            if (_buffer_object.get() != nullptr)
            {
                _buffer_object->dispose();
                _buffer_object.release();
            }
        }

        std::int32_t UniformBufferObject::binding_point() const noexcept
        {
            return _binding_point;
        }

        std::size_t UniformBufferObject::index() const noexcept
        {
            return _index;
        }

        std::size_t UniformBufferObject::size() const noexcept
        {
            return _size;
        }

        void UniformBufferObject::bind() const
        {
            glBindBufferBase(static_cast<GLenum>(_buffer_object->target()), _binding_point, _buffer_object->id());
        }

        void UniformBufferObject::create()
        {
            std::int32_t binding   = 0;
            std::int32_t blockSize = 0;

            // Get the uniform block index
            _index = glGetUniformBlockIndex(_program_id, _name.c_str());

            // Get the binding point
            glGetActiveUniformBlockiv(_program_id, _index, GL_UNIFORM_BLOCK_BINDING, &binding);

            // Get uniform block data size
            glGetActiveUniformBlockiv(_program_id, _index, GL_UNIFORM_BLOCK_DATA_SIZE, &blockSize);

            // update class members
            _binding_point = binding;
            _size          = blockSize;

            // Create the buffer object
            _buffer_object->create();

            // initialize the buffer object
            std::vector<std::uint8_t> data(_size, 0);

            _buffer_object->set_data(_size, data.data());
        }

        void UniformBufferObject::unbind() const
        {
            glBindBufferBase(static_cast<GLenum>(_buffer_object->target()), 0, 0);
        }

        std::vector<std::uint8_t> UniformBufferObject::get_data() const
        {
            return get_data(0, _size);
        }

        std::vector<std::uint8_t> UniformBufferObject::get_data(const std::size_t& offset, const std::size_t& count) const
        {
            return _buffer_object->get_data(offset, count);
        }

        void UniformBufferObject::set_data(const void* data) const
        {
            set_data(0, _size, data);
        }

        void UniformBufferObject::set_data(const std::size_t& offset, const std::size_t& count, const void* data) const
        {
            _buffer_object->set_data(offset, count, data);
        }
    }
}
