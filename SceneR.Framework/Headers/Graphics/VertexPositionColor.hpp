// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef GRAPHICS_VERTEXPOSITIONCOLOR_HPP
#define GRAPHICS_VERTEXPOSITIONCOLOR_HPP

#include <Framework/Color.hpp>
#include <Framework/Vector3.hpp>
#include "VertexDeclaration.hpp"

namespace SceneR
{
    namespace Graphics
    {
        class VertexDeclaration;

        /**
         * Describes a custom vertex format structure that contains position and color information.
         */
        struct VertexPositionColor final
        {
        private:
            /**
             * Vertex declaration, which defines per-vertex data.
             */
            static const VertexDeclaration declaration;

        public:
            /**
             * Initializes a new instance of the VertexPositionColor class with the
             * given position and color.
             */
            VertexPositionColor(const SceneR::Framework::Vector3& position
                              , const SceneR::Framework::Color&   color);

            /**
             * Releases all resources being used by this VertexPositionColor.
             */
            ~VertexPositionColor();

        private:
            /**
             * Gets the vertex position.
             */
            const SceneR::Framework::Vector3 position;

            /**
             * Gets the vertex color.
             */
            const SceneR::Framework::Color color;
        };
    }
}

#endif  // GRAPHICS_VERTEXPOSITIONCOLOR_HPP
