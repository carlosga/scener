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

#include <Framework/Core.hpp>
#include <Graphics/Effect.hpp>
#include <Graphics/IndexBuffer.hpp>
#include <Graphics/VertexBuffer.hpp>
#include <string>

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

        public:
            /**
             * Gets or sets the material Effect for this mesh part.
             */
            std::shared_ptr<Effect> GetEffect() const;

            /**
             * Gets or sets the material Effect for this mesh part.
             */
            void SetEffect(const std::shared_ptr<Effect>& effect);

            /**
             * Gets the index buffer for this mesh part.
             */
            std::shared_ptr<IndexBuffer> GetIndexBuffer();

            /**
             * Gets the number of vertices used during a draw call.
             */
            const Int32& GetVertexCount() const;

            /**
             * Gets the number of primitives to render.
             */
            const Int32& GetPrimitiveCount() const;

            /**
             * Gets the location in the index array at which to start reading vertices.
             */
            const Int32& GetStartIndex() const;

            /**
             * Gets the model mesh part tag
             */
            const std::wstring& GetTag() const;

            /**
             * Sets the model mesh part tag
             */
            void SetTag(const std::wstring& tag);

            /**
             * Gets the vertex buffer for this mesh part.
             */
            std::shared_ptr<VertexBuffer> GetVertexBuffer();

            /**
             * Gets the offset (in vertices) from the top of vertex buffer.
             */
            const Int32& GetVertexOffset() const;

        private:
            std::shared_ptr<Effect>       effect;
            std::shared_ptr<IndexBuffer>  indexBuffer;
            Int32                         vertexCount;
            Int32                         primitiveCount;
            Int32                         startIndex;
            std::wstring                  tag;
            std::shared_ptr<VertexBuffer> vertexBuffer;
            Int32                         vertexOffset;

            friend class SceneR::Content::ModelReader;
        };
    }
}

#endif  /* MODELMESHPART_HPP */
