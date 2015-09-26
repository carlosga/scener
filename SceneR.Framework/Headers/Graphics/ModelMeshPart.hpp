// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef GRAPHICS_MODELMESHPART_HPP
#define GRAPHICS_MODELMESHPART_HPP

#include <cstddef>
#include <memory>
#include <string>

#include <Graphics/PrimitiveType.hpp>

namespace SceneR
{
    namespace Content
    {
        template <typename T> class ContentTypeReader;
    }

    namespace Graphics
    {
        class EffectTechnique;
        class IndexBuffer;
        class VertexBuffer;

        /**
         * Represents a a subdivision of a ModelMesh object.
         */
        class ModelMeshPart final
        {
        public:
            /**
             * Initializes a new instance of the ModelMeshPart class.
             */
            ModelMeshPart() = default;

            /**
             * Releases all resources being used by this ModelMeshPart.
             */
            ~ModelMeshPart() = default;

        public:
            /**
             * Gets the index buffer for this mesh part.
             */
            IndexBuffer* index_buffer() const noexcept;

            /**
             * Gets the vertex buffer for this mesh part.
             */
            VertexBuffer* vertex_buffer() const noexcept;

            /**
             * Gets the location in the index array at which to start reading vertices.
             */
            std::size_t start_index() const noexcept;

            /**
             * Gets the offset (in vertices) from the top of vertex buffer.
             */
            std::size_t vertex_offset() const noexcept;

            /**
             * Gets the number of vertices used during a draw call.
             */
            std::size_t vertex_count() const noexcept;

            /**
             * Gets the number of primitives to render.
             */
            std::size_t primitive_count() const noexcept;

            /**
             * Gets the type of primitives to render.
             */
            const PrimitiveType& primitive_type() const noexcept;

        public:
            /**
             * Gets or sets the effect for this mesh part.
             */
            std::shared_ptr<EffectTechnique> effect = { nullptr };

        private:
            std::unique_ptr<IndexBuffer>    _index_buffer       = { nullptr };
            std::unique_ptr<VertexBuffer>   _vertex_buffer      = { nullptr };
            std::size_t                     _start_index        = { 0 };
            std::size_t                     _vertex_offset      = { 0 };
            std::size_t                     _vertex_count       = { 0 };
            std::size_t                     _primitive_count    = { 0 };
            SceneR::Graphics::PrimitiveType _primitive_type     = { PrimitiveType::TriangleList };

            template <typename T> friend class SceneR::Content::ContentTypeReader;
        };
    }
}

#endif  // GRAPHICS_MODELMESHPART_HPP
