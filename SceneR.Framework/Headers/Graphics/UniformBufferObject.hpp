// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef UNIFORMBUFFEROBJECT_HPP
#define UNIFORMBUFFEROBJECT_HPP

#include <vector>

#include <System/Core.hpp>
#include <Graphics/BufferObject.hpp>
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
             * @oaram programId the handle of the shader program.
             */
            UniformBufferObject(const System::String& name, const System::UInt32& programId);

            /**
             * Releases all resources being used by this UniformBufferObject.
             */
            ~UniformBufferObject();

        public:
            void Dispose() override;

        public:
            /**
             * Gets the uniform buffer block index.
             */
            System::UInt32 Index() const;

            /**
             * Gets the uniform buffer binding point.
             */
            System::Int32 BindingPoint() const;

            /**
             * Gets the uniform buffer block data size.
             */
            System::Int32 Size() const;

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
            std::vector<System::UByte> GetData() const;

            /**
             * Gets the uniform buffer data
             */
            std::vector<System::UByte> GetData(const System::UInt32& startIndex, const System::UInt32& elementCount) const;

            /**
             * Sets the uniform buffer data
             */
            void SetData(const void* data);

            /**
             * Sets the uniform buffer data
             */
            void SetData(const System::UInt32& startIndex, const System::UInt32& elementCount, const void *data);

        private:
            System::String name;
            System::UInt32 programId;
            System::UInt32 index;
            System::Int32  bindingPoint;
            System::Int32  size;
            BufferObject   bufferObject;
        };
    }
}

#endif /* UNIFORMBUFFEROBJECT_HPP */
