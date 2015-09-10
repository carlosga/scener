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
}

namespace SceneR
{
    namespace Graphics
    {
        class EffectTechnique;
        class IndexBuffer;
        class VertexBuffer;

        /**
         * Represents a a subdivision of a ModelMesh object.
         */
        class ModelMeshPart
        {
        public:
            /**
             * Initializes a new instance of the ModelMeshPart class.
             */
            ModelMeshPart();

            /**
             * Releases all resources being used by this ModelMeshPart.
             */
            ~ModelMeshPart();

        public:
            /**
             * Gets the index buffer for this mesh part.
             */
            SceneR::Graphics::IndexBuffer* index_buffer() const;

            /**
             * Gets the vertex buffer for this mesh part.
             */
            SceneR::Graphics::VertexBuffer* vertex_buffer() const;

            /**
             * Gets the location in the index array at which to start reading vertices.
             */
            std::size_t start_index() const;

            /**
             * Gets the offset (in vertices) from the top of vertex buffer.
             */
            std::size_t vertex_offset() const;

            /**
             * Gets the number of vertices used during a draw call.
             */
            std::size_t vertex_count() const;

            /**
             * Gets the number of primitives to render.
             */
            std::size_t primitive_count() const;

            /**
             * Gets the type of primitives to render.
             */
            const SceneR::Graphics::PrimitiveType& primitive_type() const;

        public:
            /**
             * Gets or sets the material EffectTechnique for this mesh part.
             */
            std::shared_ptr<SceneR::Graphics::EffectTechnique> effect;

        private:
            std::unique_ptr<SceneR::Graphics::IndexBuffer>  _index_buffer;
            std::unique_ptr<SceneR::Graphics::VertexBuffer> _vertex_buffer;
            std::size_t                                     _start_index;
            std::size_t                                     _vertex_offset;
            std::size_t                                     _vertex_count;
            std::size_t                                     _primitive_count;
            SceneR::Graphics::PrimitiveType                 _primitive_type;

            template <typename T> friend class SceneR::Content::ContentTypeReader;
        };
    }
}

#endif  // GRAPHICS_MODELMESHPART_HPP
