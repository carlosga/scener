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
            void dispose() override;

        public:
            /**
             * Gets the uniform buffer binding point.
             */
            std::int32_t binding_point() const;

            /**
             * Gets the uniform buffer block index.
             */
            std::size_t index() const;

            /**
             * Gets the uniform buffer block data size.
             */
            std::size_t size() const;

        public:
            /**
             * Activates the uniform buffer object.
             */
            void activate();

            /**
             * Deactivates the uniform buffer object.
             */
            void deactivate();

            /**
             * @brief Describe the uniform buffer object.
             */
            void describe();

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
            void set_data(const void* data);

            /**
             * Sets the uniform buffer data
             */
            void set_data(const std::size_t& offset, const std::size_t& count, const void *data);

        private:
            std::u16string _name;
            std::uint32_t  _program_id;
            std::size_t    _index;
            std::int32_t   _binding_point;
            std::size_t    _size;
            BufferView     _buffer_view;
        };
    }
}

#endif /* UNIFORMBUFFEROBJECT_HPP */
