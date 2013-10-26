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

#ifndef VERTEXELEMENT_HPP
#define VERTEXELEMENT_HPP

#include <Framework/Core.hpp>
#include <Graphics/VertexElementFormat.hpp>
#include <Graphics/VertexElementUsage.hpp>

namespace SceneR
{
    namespace Graphics
    {
        /**
         * Defines input vertex data.
         */
        class VertexElement
        {
        public:
            /**
             * Initializes a new instance of the vertex element class
             */
            VertexElement(const UInt32& offset,
                          const UInt32& componentCount,
                          const VertexElementFormat& vertexElementFormat,
                          const VertexElementUsage& vertexElementUsage,
                          const UInt32& usageIndex);

        public:
            /**
             * Gets the offset (if any) from the beginning of the stream to the beginning of the vertex data.
             */
            const UInt32& GetOffset() const;

            /**
             * Gets the number of components bases on the vertex element format.
             * @return
             */
            const UInt32& GetComponentCount() const;

            /**
             * Gets the usage data to allow the user to specify multiple usage types.
             */
            const UInt32& GetUsageIndex() const;

            /**
             * Gets or sets the format of this vertex element.
             */
            const VertexElementFormat& GetVertexElementFormat() const;

            /**
             * Gets a value describing how the vertex element is to be used.
             */
            const VertexElementUsage& GetVertexElementUsage() const;

        private:
            UInt32              offset;
            UInt32              componentCount;
            VertexElementFormat vertexElementFormat;
            VertexElementUsage  vertexElementUsage;
            UInt32              usageIndex;
        };
    }
}


#endif  /* VERTEXELEMENT_HPP */
