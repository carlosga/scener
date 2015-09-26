// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef GRAPHICS_UNIFORMBUFFEROBJECT_HPP
#define GRAPHICS_UNIFORMBUFFEROBJECT_HPP

#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include <Graphics/BufferObject.hpp>
#include <Graphics/BufferUsage.hpp>
#include <System/IDisposable.hpp>

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
            UniformBufferObject(const std::string& name, const std::uint32_t& programId) noexcept;

            /**
             * Releases all resources being used by this UniformBufferObject.
             */
            ~UniformBufferObject() = default;

        public:
            void dispose() override;

        public:
            /**
             * Gets the uniform buffer binding point.
             */
            std::int32_t binding_point() const noexcept;

            /**
             * Gets the uniform buffer block index.
             */
            std::size_t index() const noexcept;

            /**
             * Gets the uniform buffer block data size.
             */
            std::size_t size() const noexcept;

        public:
            /**
             * Activates the uniform buffer object.
             */
            void bind() const;

            /**
             * Creates the uniform buffer object.
             */
            void create();

            /**
             * Deactivates the uniform buffer object.
             */
            void unbind() const;

        public:
            /**
             * Gets the uniform buffer data
             */
            std::vector<std::uint8_t> get_data() const;

            /**
             * Gets the uniform buffer data
             */
            std::vector<std::uint8_t> get_data(const std::size_t& offset, const std::size_t& count) const;

            /**
             * Sets the uniform buffer data
             */
            void set_data(const void* data) const;

            /**
             * Sets the uniform buffer data
             */
            void set_data(const std::size_t& offset, const std::size_t& count, const void *data) const;

        private:
            std::string                   _name;
            std::uint32_t                 _program_id;
            std::size_t                   _index;
            std::int32_t                  _binding_point;
            std::size_t                   _size;
            std::unique_ptr<BufferObject> _buffer_object;
        };
    }
}

#endif  // GRAPHICS_UNIFORMBUFFEROBJECT_HPP
