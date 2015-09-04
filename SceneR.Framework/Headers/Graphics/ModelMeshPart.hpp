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
             * Gets or sets the material Effect for this mesh part.
             */
            const std::shared_ptr<SceneR::Graphics::Effect>& Effect() const;

            /**
             * Gets or sets the material Effect for this mesh part.
             */
            void Effect(const std::shared_ptr<SceneR::Graphics::Effect>& effect);

            /**
             * Gets the index buffer for this mesh part.
             */
            const std::shared_ptr<SceneR::Graphics::IndexBuffer>& IndexBuffer() const;

            /**
             * Gets the vertex buffer for this mesh part.
             */
            const std::shared_ptr<SceneR::Graphics::VertexBuffer>& VertexBuffer() const;

            /**
             * Gets the location in the index array at which to start reading vertices.
             */
            std::size_t StartIndex() const;

            /**
             * Gets the offset (in vertices) from the top of vertex buffer.
             */
            std::size_t VertexOffset() const;

            /**
             * Gets the number of vertices used during a draw call.
             */
            std::size_t VertexCount() const;

            /**
             * Gets the number of primitives to render.
             */
            std::size_t PrimitiveCount() const;

            /**
             * Gets the model mesh part tag
             */
            const std::u16string& Tag() const;

            /**
             * Sets the model mesh part tag
             */
            void Tag(const std::u16string& tag);

        private:
            std::shared_ptr<Accessor> joint              = nullptr;
            std::shared_ptr<Accessor> normal             = nullptr;
            std::shared_ptr<Accessor> position           = nullptr;
            std::shared_ptr<Accessor> textureBinormal    = nullptr;
            std::shared_ptr<Accessor> textureCoordinates = nullptr;
            std::shared_ptr<Accessor> textureTangent     = nullptr;
            std::shared_ptr<Accessor> weight             = nullptr;
            std::shared_ptr<Accessor> indices            = nullptr;
            std::shared_ptr<Material> material           = nullptr;
            PrimitiveType             type;

            std::shared_ptr<SceneR::Graphics::Effect>       effect;
            std::shared_ptr<SceneR::Graphics::IndexBuffer>  indexBuffer;
            std::shared_ptr<SceneR::Graphics::VertexBuffer> vertexBuffer;
            std::size_t                                     startIndex;
            std::size_t                                     vertexOffset;
            std::size_t                                     vertexCount;
            std::size_t                                     primitiveCount;
            std::u16string                                  tag;

            friend class SceneR::Content::MeshesReader;
            friend class SceneR::Content::ModelReader;
        };
    }
}

#endif  /* MODELMESHPART_HPP */
