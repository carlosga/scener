// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef INDEXBUFFER_HPP
#define INDEXBUFFER_HPP

#include <cstddef>
#include <cstdint>
#include <vector>

#include "BufferView.hpp"
#include <Graphics/IndexElementSize.hpp>
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
                      , const std::size_t&                        indexCount);

            /**
             * Releases all resources being used by this indexbuffer instance
             */
            ~IndexBuffer() override;

        public:
            void dispose() override;

        public:
            /**
             * Gets the number of indices in the buffer.
             */
            std::size_t index_count() const;

            /**
             * Gets the size (in bits) of each index.
             */
            const SceneR::Graphics::IndexElementSize& index_element_size() const;

            /**
             * Gets the indices buffer data
             */
            std::vector<std::uint8_t> get_data() const;

            /**
             * Gets the indices buffer data
             */
            std::vector<std::uint8_t> get_data(const std::size_t& startIndex, const std::size_t& elementCount) const;

            /**
             * Sets the indices buffer data
             */
            void set_data(const void* data);

        private:
            void activate() const;
            void deactivate() const;
            std::size_t get_element_size_in_bytes() const;

        private:
            BufferView                         _ibo;
            std::size_t                        _indexCount;
            SceneR::Graphics::IndexElementSize _indexElementSize;

            friend class GraphicsDevice;
        };
    }
}

#endif  /* INDEXBUFFER_HPP */
