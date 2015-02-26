// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef INDEXBUFFER_HPP
#define INDEXBUFFER_HPP

#include <vector>

#include <Graphics/IndexElementSize.hpp>
#include <Graphics/BufferObject.hpp>
#include <Graphics/GraphicsResource.hpp>

namespace SceneR
{
    namespace Graphics
    {
        class GraphicsDevice;

        /**
         * Describes the rendering order of the vertices in a vertex buffer.
         */
        class IndexBuffer final : public GraphicsResource
        {
        public:
            /**
             * Initializes a new instance of the IndexBuffer class.
             *
             * @param graphicsDevice the graphics device
             * @param indexElementSize the size (in bits) of each index.
             * @param indexCount the number of indices.
             */
            IndexBuffer(GraphicsDevice&                           graphicsDevice
                      , const SceneR::Graphics::IndexElementSize& indexElementSize
                      , const System::Size&                       indexCount);

            /**
             * Releases all resources being used by this indexbuffer instance
             */
            ~IndexBuffer() override;

        public:
            void Dispose() override;

        public:
            /**
             * Gets the number of indices in the buffer.
             */
            const System::Size& IndexCount() const;

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
            std::vector<System::UByte> GetData(const System::Size& startIndex
                                             , const System::Size& elementCount) const;

            /**
             * Sets the indices buffer data
             */
            void SetData(const void* data);

        private:
            void Activate() const;
            void Deactivate() const;
            System::Size GetElementSizeInBytes() const;

        private:
            BufferObject                       ibo;
            System::Size                       indexCount;
            SceneR::Graphics::IndexElementSize indexElementSize;

            friend class GraphicsDevice;
        };
    }
}

#endif  /* INDEXBUFFER_HPP */
