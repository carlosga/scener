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

#ifndef INDEXBUFFER_HPP
#define INDEXBUFFER_HPP

#include <System/Core.hpp>
#include <Graphics/GraphicsDevice.hpp>
#include <Graphics/IndexElementSize.hpp>
#include <vector>

namespace SceneR
{
    namespace Graphics
    {
        class GraphicsDevice;

        /**
         * Describes the rendering order of the vertices in a vertex buffer.
         */
        class IndexBuffer : public GraphicsResource
        {
        public:
            /**
             * Initializes a new instance of the IndexBuffer class.
             *
             * @param graphicsDevice the graphics device
             * @param indexElementSize The size (in bits) of each index.
             * @param indexCount The number of indices.
             */
            IndexBuffer(GraphicsDevice&         graphicsDevice,
                        const IndexElementSize& indexElementSize,
                        const System::UInt32&           indexCount);

            /**
             * Releases all resources being used by this indexbuffer instance
             */
            ~IndexBuffer();

        public:
            /**
             * Gets the indices count
             */
            const System::UInt32& GetIndexCount() const;

            /**
             * Gets the size (in bits) of each index.
             */
            const IndexElementSize& GetIndexElementSize() const;

            /**
             * Gets the indices buffer data
             */
            const std::vector<System::UInt32>& GetData() const;

            /**
             * Sets the indices buffer data
             */
            void SetData(const std::vector<System::UInt32>& data);

        private:
            void Release();
            void CreateIndexBuffer();
            void BindIndexBuffer()  const;
            void BufferData(const std::vector<System::UInt32>& data) const;
            void UnbindIndexBuffer() const;
            void DeleteIndexBuffer();
            const System::UInt32 GetElementSizeInBytes() const;

        private:
            System::UInt32   ibo;
            System::UInt32   indexCount;
            IndexElementSize indexElementSize;

            friend class GraphicsDevice;
        };
    }
}

#endif  /* INDEXBUFFER_HPP */
