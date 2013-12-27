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

#include <Graphics/BufferObject.hpp>
#include <Graphics/GraphicsResource.hpp>
#include <Graphics/IndexElementSize.hpp>
#include <System/Core.hpp>
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
                        const System::UInt32&   indexCount);

            /**
             * Releases all resources being used by this indexbuffer instance
             */
            virtual ~IndexBuffer();

        public:
            /**
             * Gets the indices count
             */
            const System::UInt32& IndexCount() const;

            /**
             * Gets the size (in bits) of each index.
             */
            const SceneR::Graphics::IndexElementSize& IndexElementSize() const;

            /**
             * Gets the indices buffer data
             */
            std::vector<System::UByte> GetData() const;

            /**
             * Gets the indices buffer data
             */
            std::vector<System::UByte> GetData(const System::Int32& startIndex, const System::Int32& elementCount);

            /**
             * Sets the indices buffer data
             */
            void SetData(const void* data);

            void Dump();

        private:
            void Activate() const;
            void Deactivate() const;
            const System::UInt32 GetElementSizeInBytes() const;

        private:
            BufferObject                       ibo;
            System::UInt32                     indexCount;
            SceneR::Graphics::IndexElementSize indexElementSize;

            friend class GraphicsDevice;
        };
    }
}

#endif  /* INDEXBUFFER_HPP */
