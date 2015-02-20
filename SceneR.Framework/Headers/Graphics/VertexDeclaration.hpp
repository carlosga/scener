// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef VERTEXDECLARATION_HPP
#define VERTEXDECLARATION_HPP

#include <vector>

#include <Graphics/VertexElementFormat.hpp>
#include <Graphics/VertexElementUsage.hpp>
#include <Graphics/VertexElement.hpp>

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
             * @param vertexStride The number of bytes per element.
             * @param vertexElements vertex elements.
             */
            VertexDeclaration(const System::Size&               vertexStride
                            , const std::vector<VertexElement>& vertexElements);

            /**
             * Releases all resources being used by this VertexDeclaration
             */
            ~VertexDeclaration() = default;

        public:
            /**
             * Gets the number of bytes per element.
             * @return the number of bytes per element.
             */
            const System::Size& VertexStride() const;

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
            System::Size               vertexStride;
            std::vector<VertexElement> vertexElements;

            friend class VertexBuffer;
        };
    }
}

#endif  /* VERTEXDECLARATION_HPP */
