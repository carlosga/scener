//-------------------------------------------------------------------------------
//Copyright 2013 Carlos Guzmán Álvarez
//
//Licensed under the Apache License, Version 2.0 (the "License");
//you may not use this file except in compliance with the License.
//You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//Unless required by applicable law or agreed to in writing, software
//distributed under the License is distributed on an "AS IS" BASIS,
//WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//See the License for the specific language governing permissions and
//limitations under the License.
//-------------------------------------------------------------------------------

#ifndef UNIFORMBUFFEROBJECT_HPP
#define UNIFORMBUFFEROBJECT_HPP

#include <Graphics/BufferObject.hpp>
#include <Graphics/BufferUsage.hpp>
#include <System/Core.hpp>

namespace SceneR
{
    namespace Graphics
    {
        /**
         * Represents an OpenGL Uniform Buffer Object
         *
         * http://www.opengl.org/wiki/Uniform_Buffer_Object
         */
        class UniformBufferObject : public BufferObject
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
        };
    }
}

#endif /* UNIFORMBUFFEROBJECT_HPP */
