// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef GRAPHICS_VERTEXBUFFER_HPP
#define GRAPHICS_VERTEXBUFFER_HPP

#include <cstddef>
#include <cstdint>
#include <memory>
#include <vector>

#include <Graphics/BufferObject.hpp>
#include <Graphics/GraphicsResource.hpp>
#include <Graphics/VertexArrayObject.hpp>
#include <Graphics/VertexDeclaration.hpp>

namespace SceneR
{
    namespace Content
    {
        template <typename T> class ContentTypeReader;
    }

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
            VertexBuffer(gsl::not_null<GraphicsDevice*>     graphicsDevice
                       , const std::size_t&                 vertexCount
                       , std::unique_ptr<VertexDeclaration> vertexDeclaration) noexcept;

            /**
             * Releases all resources being used by the current VertexBuffer
             */
            ~VertexBuffer() = default;

        public:
            void dispose() override;

        public:
            /**
             * Gets the number of vertex for the current buffer
             */
            std::size_t vertex_count() const noexcept;

            /**
             * Gets the vertex buffer data
             */
            std::vector<std::uint8_t> get_data() const;

            /**
             * Gets the vertex buffer data
             */
            std::vector<std::uint8_t> get_data(const std::size_t& startIndex, const std::size_t& elementCount) const;

            /**
             * Sets the vertex buffer data
             */
            void set_data(const gsl::span<std::uint8_t>& data) const;

            /**
             * Defines per-vertex data in a buffer.
             */
            SceneR::Graphics::VertexDeclaration* vertex_declaration() const noexcept;

        private:
            void bind();
            void unbind();
            void initialize();

        private:
            std::uint32_t                      _binding_index;
            std::size_t                        _vertex_count;
            std::unique_ptr<VertexDeclaration> _vertex_declaration;
            std::unique_ptr<VertexArrayObject> _vao;
            std::unique_ptr<BufferObject>      _vbo;

            friend class SceneR::Graphics::GraphicsDevice;
            template <typename T> friend class SceneR::Content::ContentTypeReader;
        };
    }
}

#endif  // GRAPHICS_VERTEXBUFFER_HPP
