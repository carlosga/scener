// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef VERTEXDECLARATION_HPP
#define VERTEXDECLARATION_HPP

#include <stdint.h>
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
        class VertexDeclaration final
        {
        public:
            /**
             * Initializes a new instance of the VertexDeclaration class.
             *
             * @param vertexStride The number of bytes per element.
             * @param vertexElements vertex elements.
             */
            VertexDeclaration(const uint32_t&                   vertexStride
                            , const std::vector<VertexElement>& vertexElements);

            /**
             * @brief Copy constructor
             * @param declaration the vertex declaration to copy from
             */
            VertexDeclaration(const VertexDeclaration& declaration);

            /**
             * Destructor
             */
            ~VertexDeclaration();

        public:
            /**
             * Gets the number of bytes per element.
             * @return the number of bytes per element.
             */
            uint32_t VertexStride() const;

            /**
             * Gets the vertex elements.
             * @return the vertex elements.
             */
            const std::vector<VertexElement>& VertexElements() const;

        public:
            VertexDeclaration& operator=(const VertexDeclaration& declaration);

        private:
            /**
             * Declares the vertex format to be used on drawing operations.
             * @param vaoiId Specifies the name of the vertex array object for glDisableVertexArrayAttrib and glEnableVertexArrayAttrib functions.
             * @param bindingIndex The index of the vertex buffer binding with which to associate the generic vertex attribute.
             */
            void Declare(const uint32_t& vaoId, const uint32_t& bindingIndex​) const;

            uint32_t GetElementCount(const VertexElementFormat& vertexFormat) const;
            uint32_t GetElementType(const VertexElementFormat& vertexFormat) const;

        private:
            uint32_t                   vertexStride;
            std::vector<VertexElement> vertexElements;

            friend class VertexBuffer;
        };
    }
}

#endif  /* VERTEXDECLARATION_HPP */
