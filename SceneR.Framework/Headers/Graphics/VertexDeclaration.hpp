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

#include <Framework/Core.hpp>
#include <Graphics/VertexElement.hpp>
#include <vector>

namespace SceneR
{
    namespace Graphics
    {
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
            VertexDeclaration(const UInt32& componentCount,
                              const UInt32& vertexStride,
                              const std::vector<VertexElement>& vertexElements);

        public:
            /**
             * Gets the total number of components.
             * @return the total number of components
             */
            const UInt32& GetComponentCount() const;

            /**
             * Gets the number of bytes per element.
             * @return the number of bytes per element.
             */
            const UInt32& GetVertexStride() const;

            /**
             * Gets the vertex elements.
             * @return the vertex elements.
             */
            const std::vector<VertexElement>& GetVertexElements() const;

        private:
            UInt32                     componentCount;
            UInt32                     vertexStride;
            std::vector<VertexElement> vertexElements;
        };
    }
}

#endif  /* VERTEXDECLARATION_HPP */
