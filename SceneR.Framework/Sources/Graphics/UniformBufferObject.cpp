// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/UniformBufferObject.hpp>

#include <System/Graphics/Platform.hpp>
#include <System/Text/Encoding.hpp>

namespace SceneR
{
    namespace Graphics
    {
        using System::Text::Encoding;

        UniformBufferObject::UniformBufferObject(const std::u16string& name, const std::uint32_t& programId)
            : name         { name }
            , programId    { programId }
            , index        { 0 }
            , bindingPoint { 0 }
            , size         { 0 }
            , bufferObject { BufferTarget::UniformBuffer, BufferUsage::DynamicDraw }
        {
        }

        UniformBufferObject::~UniformBufferObject()
        {
        }

        void UniformBufferObject::Dispose()
        {
            this->bufferObject.Dispose();
        }

        std::int32_t UniformBufferObject::BindingPoint() const
        {
            return this->bindingPoint;
        }

        std::size_t UniformBufferObject::Index() const
        {
            return this->index;
        }

        std::size_t UniformBufferObject::Size() const
        {
            return this->size;
        }

        void UniformBufferObject::Activate()
        {
            glBindBufferBase(static_cast<GLenum>(this->bufferObject.Target())
                           , this->bindingPoint
                           , this->bufferObject.Id());
        }

        void UniformBufferObject::Deactivate()
        {
            glBindBufferBase(static_cast<GLenum>(this->bufferObject.Target()), 0, 0);
        }

        std::vector<std::uint8_t> UniformBufferObject::GetData() const
        {
            return this->GetData(0, this->size);
        }

        std::vector<std::uint8_t> UniformBufferObject::GetData(const std::size_t& startIndex
                                                             , const std::size_t& elementCount) const
        {
            auto data = std::vector<std::uint8_t>(elementCount, 0);

            this->bufferObject.GetData(startIndex, elementCount, data.data());

            return data;
        }

        void UniformBufferObject::SetData(const void* data)
        {
            this->bufferObject.BufferData(0, this->size, data);
        }

        void UniformBufferObject::SetData(const std::size_t& startIndex
                                        , const std::size_t& elementCount
                                        , const void*        data)
        {
            if (data == nullptr)
            {
                return;
            }

            this->bufferObject.BufferData(startIndex, elementCount, data);
        }

        void UniformBufferObject::Describe()
        {
            std::string  tmp       = Encoding::Convert(this->name);
            std::int32_t binding   = 0;
            std::int32_t blockSize = 0;

            // Get the uniform block index
            this->index = glGetUniformBlockIndex(this->programId, tmp.c_str());

            // Get the binding point
            glGetActiveUniformBlockiv(this->programId, this->index, GL_UNIFORM_BLOCK_BINDING, &binding);

            // Get uniform block data size
            glGetActiveUniformBlockiv(this->programId, this->index, GL_UNIFORM_BLOCK_DATA_SIZE, &blockSize);

            // Update class members
            this->bindingPoint = binding;
            this->size         = blockSize;

            // Initialize the buffer object
            std::vector<std::uint8_t> data(this->size, 0);

            this->bufferObject.BufferData(this->size, data.data());
        }
    }
}
