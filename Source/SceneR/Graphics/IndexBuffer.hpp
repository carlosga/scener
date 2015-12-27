// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_INDEXBUFFER_HPP
#define SCENER_GRAPHICS_INDEXBUFFER_HPP

#include <cstddef>
#include <cstdint>
#include <memory>
#include <vector>

#include <gsl.h>

#include "ComponentType.hpp"
#include "GraphicsResource.hpp"

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
            IndexBuffer(gsl::not_null<GraphicsDevice*> graphicsDevice
                      , const ComponentType&           indexElementType
                      , const std::size_t&             indexCount) noexcept;

            /**
             * Releases all resources being used by this indexbuffer instance
             */
            virtual ~IndexBuffer() override = default;

        public:
            virtual void dispose() override;

        public:
            /**
             * Gets the number of indices in the buffer.
             */
            std::size_t index_count() const noexcept;

            /**
             * Gets the type of each index.
             */
            const ComponentType& index_element_type() const noexcept;

            /**
             * Gets the size (in bytes) of each index.
             * @return the size (in bytes) of each index.
             */
            std::size_t element_size_in_bytes() const noexcept;

            /**
             * Gets the indices buffer data
             */
            std::vector<std::uint8_t> get_data() const noexcept;

            /**
             * Gets the indices buffer data
             */
            std::vector<std::uint8_t> get_data(const std::size_t& startIndex
                                             , const std::size_t& elementCount) const noexcept;

            /**
             * Sets the indices buffer data
             */
            void set_data(const gsl::span<std::uint8_t>& data) const noexcept;

        private:
            void bind() const noexcept;
            void unbind() const noexcept;
            void create() noexcept;

        private:
            std::unique_ptr<BufferObject> _ibo;
            std::size_t                   _indexCount;
            ComponentType                 _indexElementType;

            friend class SceneR::Graphics::GraphicsDevice;
        };
    }
}

#endif // SCENER_GRAPHICS_INDEXBUFFER_HPP
