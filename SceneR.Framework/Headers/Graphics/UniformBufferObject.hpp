// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef UNIFORMBUFFEROBJECT_HPP
#define UNIFORMBUFFEROBJECT_HPP

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
        class UniformBufferObject
        {
        public:
            /**
             * Initializes a new instance of the UniformBufferObject class.
             */
            UniformBufferObject(const BufferUsage& usage);

            /**
             * Releases all resources being used by this UniformBufferObject.
             */
            virtual ~UniformBufferObject();

        private:
            BufferObject ubo;
        };
    }
}

#endif /* UNIFORMBUFFEROBJECT_HPP */
