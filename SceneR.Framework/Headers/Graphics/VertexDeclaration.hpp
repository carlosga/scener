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

#ifndef VERTEXDECLARATION_HPP
#define VERTEXDECLARATION_HPP

#include <Graphics/VertexElement.hpp>
#include <Graphics/VertexElementFormat.hpp>
#include <Graphics/VertexElementUsage.hpp>
#include <System/Core.hpp>
#include <vector>

namespace SceneR
{
    namespace Graphics
    {
        class VertexBuffer;

        /**
         * A vertex declaration, which defines per-vertex data.
         */
        class VertexDeclaration
        {
        public:
            /**
             * Initializes a new instance of the VertexDeclaration class.
             *
             * @param componentCount The total number of components.
             * @param vertexStride The number of bytes per element.
             * @param vertexElements vertex elements.
             */
            VertexDeclaration(const System::UInt32&             vertexStride,
                              const std::vector<VertexElement>& vertexElements);

        public:
            /**
             * Gets the number of bytes per element.
             * @return the number of bytes per element.
             */
            const System::UInt32& VertexStride() const;

            /**
             * Gets the vertex elements.
             * @return the vertex elements.
             */
            const std::vector<VertexElement>& VertexElements() const;

        private:
            /**
             * Activates the vertex format to be used on drawing operations.
             */
            void Activate() const;

            /**
             * Deactivates the vertex format to be used on drawing operations.
             */
            void Deactivate() const;

            System::UInt32 GetElementCount(const VertexElementFormat& vertexFormat) const;
            System::UInt32 GetElementType(const VertexElementFormat& vertexFormat) const;
            System::UInt32 GetUsageIndex(const VertexElementUsage& usage) const;

        private:
            System::UInt32             vertexStride;
            std::vector<VertexElement> vertexElements;

            friend class VertexBuffer;
        };
    }
}

#endif  /* VERTEXDECLARATION_HPP */
