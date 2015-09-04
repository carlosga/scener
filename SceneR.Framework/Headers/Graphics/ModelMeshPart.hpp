// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef MODELMESHPART_HPP
#define MODELMESHPART_HPP

#include <cstddef>
#include <memory>
#include <string>

#include <Graphics/PrimitiveType.hpp>

namespace SceneR
{
    namespace Content
    {
        class ModelReader;
        class MeshesReader;
    }
}

namespace SceneR
{
    namespace Graphics
    {
        class Accessor;
        class Effect;
        class IndexBuffer;
        class Material;
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
            const std::shared_ptr<SceneR::Graphics::IndexBuffer>& index_buffer() const;

            /**
             * Gets the vertex buffer for this mesh part.
             */
            const std::shared_ptr<SceneR::Graphics::VertexBuffer>& vertex_buffer() const;

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

        public:
            /**
             * Gets or sets the tag for this mesh part.
             */
            std::shared_ptr<SceneR::Graphics::Effect> effect;

            /**
             * Gets or sets the material Effect for this mesh part.
             */
            std::u16string tag;

        private:
            std::shared_ptr<SceneR::Graphics::IndexBuffer>  _index_buffer;
            std::shared_ptr<SceneR::Graphics::VertexBuffer> _vertex_buffer;
            std::size_t                                     _start_index;
            std::size_t                                     _vertex_offset;
            std::size_t                                     _vertex_count;
            std::size_t                                     _primitive_count;

            std::shared_ptr<Accessor> _joint              = nullptr;
            std::shared_ptr<Accessor> _normal             = nullptr;
            std::shared_ptr<Accessor> _position           = nullptr;
            std::shared_ptr<Accessor> _textureBinormal    = nullptr;
            std::shared_ptr<Accessor> _textureCoordinates = nullptr;
            std::shared_ptr<Accessor> _textureTangent     = nullptr;
            std::shared_ptr<Accessor> _weight             = nullptr;
            std::shared_ptr<Accessor> _indices            = nullptr;
            std::shared_ptr<Material> _material           = nullptr;
            PrimitiveType             _type;

            friend class SceneR::Content::MeshesReader;
            friend class SceneR::Content::ModelReader;
        };
    }
}

#endif  /* MODELMESHPART_HPP */
