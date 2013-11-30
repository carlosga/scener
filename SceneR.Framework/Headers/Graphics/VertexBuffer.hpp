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

#include <System/Core.hpp>
#include <Graphics/GraphicsDevice.hpp>
#include <stdexcept>
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
            VertexBuffer(GraphicsDevice& graphicsDevice);

            /**
             * Releases all resources being used by the current VertexBuffer
             */
            ~VertexBuffer();

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
            template <class T>
            void SetData(const std::vector<T>& data)
            {
                throw std::runtime_error("Unknown vertex type");
            };

        private:
            void CreateVertexBuffer();
            void BindVertexBuffer() const;
            void UnbindVertexBuffer() const;
            void DeleteVertexBuffer();
            void CreateVertexArray();
            void BindVertexArray() const;
            void UnbindVertexArray() const;
            void DeleteVertexArray();
            void DeclareVertexFormat(const VertexDeclaration& vDecl) const;
            void BufferData(const VertexDeclaration& vDecl, const System::UInt32& count, const GLvoid* data);
            void Release();

        private:
            System::UInt32 vertexCount;
            System::UInt32 vbo;
            System::UInt32 vao;

            friend class GraphicsDevice;
        };
    }
}

#endif  /* VERTEXBUFFER_HPP */
