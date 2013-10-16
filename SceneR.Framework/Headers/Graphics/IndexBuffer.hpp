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

#include <vector>
#include "Core/Core.hpp"
#include "Graphics/GraphicsResource.hpp"
#include "Graphics/IndexElementSize.hpp"

namespace SceneR
{
    namespace Graphics
    {
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
            IndexBuffer (GraphicsDevice&         graphicsDevice,
                         const IndexElementSize& indexElementSize,
                         const UInt32&           indexCount);

            /**
             * Releases all resources being used by this indexbuffer instance
             */
            ~IndexBuffer();

        public:
            /**
             * Gets the indices count
             */
            const UInt32& GetIndexCount() const;

            /**
             * Gets the size (in bits) of each index.
             */
            const IndexElementSize& GetIndexElementSize() const;

            /**
             * Gets the indices buffer data
             */
            const std::vector<UInt32>& GetData() const;

            /**
             * Sets the indices buffer data
             */
            void SetData(const std::vector<UInt32>& data);

        private:
            void Release();
            void CreateVertexElementBuffer();
            void BindVertexElementBuffer()  const;
            void BufferData(const std::vector<UInt32>& data) const;
            void UnbindVertexElementBuffer() const;
            void DeleteVertexElementBuffer();
            const UInt32 GetElementSizeInBytes() const;

        private:
            UInt32           ibo;
            UInt32           indexCount;
            IndexElementSize indexElementSize;

            friend class GraphicsDevice;
        };
    }
}

#endif  /* INDEXBUFFER_HPP */
