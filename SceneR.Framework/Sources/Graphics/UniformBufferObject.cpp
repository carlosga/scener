// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/UniformBufferObject.hpp>

#include <Graphics/BufferObject.hpp>
#include <System/Graphics/Platform.hpp>
#include <System/Text/Encoding.hpp>

namespace SceneR
{
    namespace Graphics
    {
        using SceneR::Graphics::BufferObject;
        using System::Text::Encoding;

        UniformBufferObject::UniformBufferObject(const std::u16string& name, const std::uint32_t& programId)
            : _name          { name }
            , _program_id    { programId }
            , _index         { 0 }
            , _binding_point { 0 }
            , _size          { 0 }
            , _buffer_object { std::make_unique<BufferObject>(BufferTarget::UniformBuffer, BufferUsage::DynamicDraw) }
        {
        }

        UniformBufferObject::~UniformBufferObject()
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

        std::int32_t UniformBufferObject::binding_point() const
        {
            return _binding_point;
        }

        std::size_t UniformBufferObject::index() const
        {
            return _index;
        }

        std::size_t UniformBufferObject::size() const
        {
            return _size;
        }

        void UniformBufferObject::activate()
        {
            glBindBufferBase(static_cast<GLenum>(_buffer_object->target()), _binding_point, _buffer_object->id());
        }

        void UniformBufferObject::deactivate()
        {
            glBindBufferBase(static_cast<GLenum>(_buffer_object->target()), 0, 0);
        }

        std::vector<std::uint8_t> UniformBufferObject::get_data() const
        {
            return get_data(0, _size);
        }

        std::vector<std::uint8_t> UniformBufferObject::get_data(const std::size_t& offset, const std::size_t& count) const
        {
            auto data = std::vector<std::uint8_t>(count, 0);

            _buffer_object->get_data(offset, count, data.data());

            return data;
        }

        void UniformBufferObject::set_data(const void* data)
        {
            _buffer_object->set_data(0, _size, data);
        }

        void UniformBufferObject::set_data(const std::size_t& offset, const std::size_t& count, const void* data)
        {
            if (data == nullptr)
            {
                return;
            }

            _buffer_object->set_data(offset, count, data);
        }

        void UniformBufferObject::describe()
        {
            std::string  tmp       = Encoding::convert(_name);
            std::int32_t binding   = 0;
            std::int32_t blockSize = 0;

            // Create the buffer object
            _buffer_object->create();

            // Get the uniform block index
            _index = glGetUniformBlockIndex(_program_id, tmp.c_str());

            // Get the binding point
            glGetActiveUniformBlockiv(_program_id, _index, GL_UNIFORM_BLOCK_BINDING, &binding);

            // Get uniform block data size
            glGetActiveUniformBlockiv(_program_id, _index, GL_UNIFORM_BLOCK_DATA_SIZE, &blockSize);

            // update class members
            _binding_point = binding;
            _size          = blockSize;

            // initialize the buffer object
            std::vector<std::uint8_t> data(_size, 0);

            _buffer_object->set_data(_size, data.data());
        }
    }
}
