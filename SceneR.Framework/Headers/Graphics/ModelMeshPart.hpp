// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef MODELMESHPART_HPP
#define MODELMESHPART_HPP

#include <memory>

#include <System/Core.hpp>

namespace SceneR
{
    namespace Content
    {
        class ModelReader;
    }
}

namespace SceneR
{
    namespace Graphics
    {
        class Effect;
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
            const System::UInt32& StartIndex() const;

            /**
             * Gets the offset (in vertices) from the top of vertex buffer.
             */
            const System::UInt32& VertexOffset() const;

            /**
             * Gets the number of vertices used during a draw call.
             */
            const System::UInt32& VertexCount() const;

            /**
             * Gets the number of primitives to render.
             */
            const System::UInt32& PrimitiveCount() const;

            /**
             * Gets the model mesh part tag
             */
            const System::String& Tag() const;

            /**
             * Sets the model mesh part tag
             */
            void Tag(const System::String& tag);

        private:
            std::shared_ptr<SceneR::Graphics::Effect>       effect;
            std::shared_ptr<SceneR::Graphics::IndexBuffer>  indexBuffer;
            std::shared_ptr<SceneR::Graphics::VertexBuffer> vertexBuffer;
            System::UInt32                                  startIndex;
            System::UInt32                                  vertexOffset;
            System::UInt32                                  vertexCount;
            System::UInt32                                  primitiveCount;
            System::String                                  tag;

            friend class SceneR::Content::ModelReader;
        };
    }
}

#endif  /* MODELMESHPART_HPP */
