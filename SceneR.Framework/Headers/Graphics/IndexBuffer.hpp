// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef GRAPHICS_INDEXBUFFER_HPP
#define GRAPHICS_INDEXBUFFER_HPP

#include <cstddef>
#include <cstdint>
#include <memory>
#include <vector>

#include <Graphics/ComponentType.hpp>
#include <Graphics/GraphicsResource.hpp>

namespace SceneR
{
    namespace Content
    {
        template <typename T> class ContentTypeReader;
    }
}

namespace SceneR
{
    namespace Graphics
    {
        class BufferObject;
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
             * @param indexElementType the type of each index.
             * @param indexCount the number of indices.
             */
            IndexBuffer(GraphicsDevice&                        graphicsDevice
                      , const SceneR::Graphics::ComponentType& indexElementType
                      , const std::size_t&                     indexCount);

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
             * Gets the type of each index.
             */
            const SceneR::Graphics::ComponentType& index_element_type() const;

            /**
             * Gets the size (in bytes) of each index.
             * @return the size (in bytes) of each index.
             */
            std::size_t element_size_in_bytes() const;

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
            void initialize();

        private:
            std::unique_ptr<BufferObject>   _ibo;
            std::size_t                     _indexCount;
            SceneR::Graphics::ComponentType _indexElementType;

            friend class SceneR::Graphics::GraphicsDevice;
            template <typename T> friend class SceneR::Content::ContentTypeReader;
        };
    }
}

#endif  // GRAPHICS_INDEXBUFFER_HPP
