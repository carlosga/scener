// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef UNIFORMBUFFEROBJECT_HPP
#define UNIFORMBUFFEROBJECT_HPP

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include "BufferView.hpp"
#include <Graphics/BufferUsage.hpp>

namespace SceneR
{
    namespace Graphics
    {
        /**
         * Represents an OpenGL Uniform Buffer Object
         *
         * http://www.opengl.org/wiki/Uniform_Buffer_Object
         */
        class UniformBufferObject final : System::IDisposable
        {
        public:
            /**
             * Initializes a new instance of the UniformBufferObject class.
             * @param name the name of the uniform buffer object.
             * @param programId the handle of the shader program.
             */
            UniformBufferObject(const std::u16string& name, const std::uint32_t& programId);

            /**
             * Releases all resources being used by this UniformBufferObject.
             */
            ~UniformBufferObject();

        public:
            void Dispose() override;

        public:
            /**
             * Gets the uniform buffer binding point.
             */
            std::int32_t BindingPoint() const;

            /**
             * Gets the uniform buffer block index.
             */
            std::size_t Index() const;

            /**
             * Gets the uniform buffer block data size.
             */
            std::size_t Size() const;

        public:
            /**
             * Activates the uniform buffer object.
             */
            void Activate();

            /**
             * Deactivates the uniform buffer object.
             */
            void Deactivate();

        public:
            /**
             * @brief Describe the uniform buffer object.
             */
            void Describe();

        public:
            /**
             * Gets the uniform buffer data
             */
            std::vector<std::uint8_t> GetData() const;

            /**
             * Gets the uniform buffer data
             */
            std::vector<std::uint8_t> GetData(const std::size_t& startIndex, const std::size_t& elementCount) const;

            /**
             * Sets the uniform buffer data
             */
            void SetData(const void* data);

            /**
             * Sets the uniform buffer data
             */
            void SetData(const std::size_t& startIndex, const std::size_t& elementCount, const void *data);

        private:
            std::u16string name;
            std::uint32_t  programId;
            std::size_t    index;
            std::int32_t   bindingPoint;
            std::size_t    size;
            BufferView     bufferView;
        };
    }
}

#endif /* UNIFORMBUFFEROBJECT_HPP */
