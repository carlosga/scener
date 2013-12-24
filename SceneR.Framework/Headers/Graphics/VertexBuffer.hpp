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

#ifndef VERTEXBUFFER_HPP
#define VERTEXBUFFER_HPP

#include <Graphics/BufferObject.hpp>
#include <Graphics/GraphicsResource.hpp>
#include <Graphics/VertexArrayObject.hpp>
#include <System/Core.hpp>
#include <memory>
#include <vector>

namespace SceneR
{
    namespace Graphics
    {
        class GraphicsDevice;
        class VertexDeclaration;

        /**
         * Represents a list of 3D vertices to be streamed to the graphics device.
         */
        class VertexBuffer : public GraphicsResource
        {
        public:
            /**
             * Initializes a new instance of the VertexBuffer class.
             * @param graphicsDevice the graphics device.
             */
            VertexBuffer(GraphicsDevice&                                      graphicsDevice
                       , System::UInt32                                       vertexCount
                       , std::shared_ptr<SceneR::Graphics::VertexDeclaration> vertexDeclaration);

            /**
             * Releases all resources being used by the current VertexBuffer
             */
            virtual ~VertexBuffer();

        public:
            /**
             * Gets the number of vertex for the current buffer
             */
            const System::UInt32& VertexCount() const;

            /**
             * Gets the vertex buffer data
             */
            const std::vector<System::Single>& GetData() const;

            /**
             * Sets the vertex buffer data
             */
            void SetData(const void* data);

            /**
             * Defines per-vertex data in a buffer.
             */
            std::shared_ptr<SceneR::Graphics::VertexDeclaration> VertexDeclaration();

        private:
            void Activate();
            void Deactivate();

        private:
            std::shared_ptr<SceneR::Graphics::VertexDeclaration> vertexDeclaration;
            System::UInt32                                       vertexCount;
            VertexArrayObject                                    vao;
            BufferObject                                         vbo;

            friend class GraphicsDevice;
        };
    }
}

#endif  /* VERTEXBUFFER_HPP */
