//-------------------------------------------------------------------------------
//Copyright 2013 Carlos Guzmán Álvarez
//
//Licensed under the Apache License, Version 2.0 (the "License");
//you may not use this file except in compliance with the License.
//You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//Unless required by applicable law or agreed to in writing, software
//distributed under the License is distributed on an "AS IS" BASIS,
//WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//See the License for the specific language governing permissions and
//limitations under the License.
//-------------------------------------------------------------------------------

#ifndef MODELMESHPART_HPP
#define MODELMESHPART_HPP

#include <Graphics/Effect.hpp>
#include <Graphics/IndexBuffer.hpp>
#include <Graphics/VertexBuffer.hpp>
#include <System/Core.hpp>
#include <memory>

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
             * Gets the number of vertices used during a draw call.
             */
            const System::Int32& VertexCount() const;

            /**
             * Gets the number of primitives to render.
             */
            const System::Int32& PrimitiveCount() const;

            /**
             * Gets the location in the index array at which to start reading vertices.
             */
            const System::Int32& StartIndex() const;

            /**
             * Gets the model mesh part tag
             */
            const System::String& Tag() const;

            /**
             * Sets the model mesh part tag
             */
            void Tag(const System::String& tag);

            /**
             * Gets the vertex buffer for this mesh part.
             */
            const std::shared_ptr<SceneR::Graphics::VertexBuffer>& VertexBuffer() const;

            /**
             * Gets the offset (in vertices) from the top of vertex buffer.
             */
            const System::Int32& VertexOffset() const;

        private:
            std::shared_ptr<SceneR::Graphics::Effect>       effect;
            std::shared_ptr<SceneR::Graphics::IndexBuffer>  indexBuffer;
            System::Int32                                   vertexCount;
            System::Int32                                   primitiveCount;
            System::Int32                                   startIndex;
            System::String                                  tag;
            std::shared_ptr<SceneR::Graphics::VertexBuffer> vertexBuffer;
            System::Int32                                   vertexOffset;

            friend class SceneR::Content::ModelReader;
        };
    }
}

#endif  /* MODELMESHPART_HPP */
