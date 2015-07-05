// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef VERTEXELEMENT_HPP
#define VERTEXELEMENT_HPP

#include <cstddef>
#include <cstdint>

#include <Graphics/VertexElementFormat.hpp>
#include <Graphics/VertexElementUsage.hpp>

namespace SceneR
{
    namespace Graphics
    {
        /**
         * Defines input vertex data.
         */
        class VertexElement final
        {
        public:
            /**
             * Initializes a new instance of the vertex element class
             */
            VertexElement(const std::size_t&                           offset
                        , const SceneR::Graphics::VertexElementFormat& vertexElementFormat
                        , const SceneR::Graphics::VertexElementUsage&  vertexElementUsage
                        , const std::uint32_t&                         usageIndex);

            /**
             * @brief Copy constructor
             * @param element the vertex element to copy from
             */
            VertexElement(const VertexElement& element);

            /**
             * Releases all resources being used by this VertexElement.
             */
            ~VertexElement();

        public:
            /**
             * Gets the offset (if any) from the beginning of the stream to the beginning of the vertex data.
             */
            std::size_t Offset() const;

            /**
             * Gets the usage data to allow the user to specify multiple usage types.
             */
            std::uint32_t UsageIndex() const;

            /**
             * Gets or sets the format of this vertex element.
             */
            const SceneR::Graphics::VertexElementFormat& VertexElementFormat() const;

            /**
             * Gets a value describing how the vertex element is to be used.
             */
            const SceneR::Graphics::VertexElementUsage& VertexElementUsage() const;

        public:
            VertexElement& operator=(const VertexElement& element);

        private:
            std::size_t                           offset;
            SceneR::Graphics::VertexElementFormat vertexElementFormat;
            SceneR::Graphics::VertexElementUsage  vertexElementUsage;
            std::uint32_t                         usageIndex;
        };
    }
}

#endif  /* VERTEXELEMENT_HPP */
