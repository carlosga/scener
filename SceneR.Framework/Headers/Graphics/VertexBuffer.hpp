// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef VERTEXBUFFER_HPP
#define VERTEXBUFFER_HPP

#include <cstddef>
#include <cstdint>
#include <memory>
#include <vector>

#include <Graphics/BufferObject.hpp>
#include <Graphics/GraphicsResource.hpp>
#include <Graphics/VertexArrayObject.hpp>

namespace SceneR
{
    namespace Graphics
    {
        class GraphicsDevice;
        class VertexDeclaration;

        /**
         * Represents a list of 3D vertices to be streamed to the graphics device.
         */
        class VertexBuffer final : public GraphicsResource
        {
        public:
            /**
             * Initializes a new instance of the VertexBuffer class.
             * @param graphicsDevice the graphics device.
             */
            VertexBuffer(GraphicsDevice&                                             graphicsDevice
                       , const std::size_t&                                          vertexCount
                       , const std::shared_ptr<SceneR::Graphics::VertexDeclaration>& vertexDeclaration);

            /**
             * Releases all resources being used by the current VertexBuffer
             */
            ~VertexBuffer() override;

        public:
            void Dispose() override;

        public:
            /**
             * Gets the number of vertex for the current buffer
             */
            std::size_t VertexCount() const;

            /**
             * Gets the vertex buffer data
             */
            std::vector<std::uint8_t> GetData() const;

            /**
             * Gets the vertex buffer data
             */
            std::vector<std::uint8_t> GetData(const std::size_t& startIndex, const std::size_t& elementCount) const;

            /**
             * Sets the vertex buffer data
             */
            void SetData(const void* data);

            /**
             * Defines per-vertex data in a buffer.
             */
            std::shared_ptr<SceneR::Graphics::VertexDeclaration> VertexDeclaration() const;

        private:
            void Activate();
            void Deactivate();

        private:
            std::uint32_t                                        bindingIndex;
            std::shared_ptr<SceneR::Graphics::VertexDeclaration> vertexDeclaration;
            std::size_t                                          vertexCount;
            VertexArrayObject                                    vao;
            BufferObject                                         vbo;

            friend class GraphicsDevice;
        };
    }
}

#endif  /* VERTEXBUFFER_HPP */
