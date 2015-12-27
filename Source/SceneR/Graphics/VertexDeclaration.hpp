// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_VERTEXDECLARATION_HPP
#define SCENER_GRAPHICS_VERTEXDECLARATION_HPP

#include <cstddef>
#include <cstdint>
#include <vector>

#include "VertexElement.hpp"

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
            VertexDeclaration(const std::size_t& vertexStride, const std::vector<VertexElement>& vertexElements) noexcept;

            /**
             * @brief Copy constructor
             * @param declaration the vertex declaration to copy from
             */
            VertexDeclaration(const VertexDeclaration& declaration) = default;

            /**
             * Destructor
             */
            ~VertexDeclaration() = default;

        public:
            /**
             * Gets the number of bytes per element.
             * @return the number of bytes per element.
             */
            std::size_t vertex_stride() const noexcept;

            /**
             * Gets the vertex elements.
             * @return the vertex elements.
             */
            const std::vector<VertexElement>& vertex_elements() const noexcept;

        public:
            VertexDeclaration& operator=(const VertexDeclaration& declaration) = default;

        private:
            /**
             * Declares the vertex format to be used on drawing operations.
             * @param vaoId Specifies the name of the vertex array object for glDisableVertexArrayAttrib and glEnableVertexArrayAttrib functions.
             * @param bindingIndex The index of the vertex buffer binding with which to associate the generic vertex attribute.
             */
            void declare(const std::uint32_t& vaoId, const std::uint32_t& bindingIndex) const;

            std::size_t get_element_count(const VertexElementFormat& vertexFormat) const noexcept;

            std::uint32_t get_element_type(const VertexElementFormat& vertexFormat) const noexcept;

        private:
            std::size_t                _vertex_stride;
            std::vector<VertexElement> _vertex_elements;

            friend class VertexBuffer;
        };
    }
}

#endif // SCENER_GRAPHICS_VERTEXDECLARATION_HPP */
