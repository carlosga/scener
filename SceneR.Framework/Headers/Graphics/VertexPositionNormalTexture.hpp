// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef GRAPHICS_VERTEXPOSITIONNORMALTEXTURE_HPP
#define GRAPHICS_VERTEXPOSITIONNORMALTEXTURE_HPP

#include <Framework/Vector2.hpp>
#include <Framework/Vector3.hpp>

namespace SceneR
{
    namespace Graphics
    {
        class VertexDeclaration;

        /**
         * Describes a vertex format that contains position, normal data, and texture coordinates.
         */
        struct VertexPositionNormalTexture final
        {
        public:
            /**
             * Gets the vertex declaration
             */
            static const VertexDeclaration declaration;

        public:
            /**
             * Initializes a new instance of the VertexPositionNormalTexture class
             * with the given position, normal and texture coordinates.
             */
            VertexPositionNormalTexture(const SceneR::Framework::Vector3& position
                                      , const SceneR::Framework::Vector3& normal
                                      , const SceneR::Framework::Vector2& textureCoordinate);

            /**
             * Releases all resources being used by this VertexPositionNormalTexture.
             */
            ~VertexPositionNormalTexture();

        private:
            /**
             * Gets the vertex position
             */
            SceneR::Framework::Vector3 position;

            /**
             * Gets the vertex normal
             */
            SceneR::Framework::Vector3 normal;

            /**
             * Gets the vertex texture coordinates
             */
            SceneR::Framework::Vector2 texture_coordinate;
        };
    }
}

#endif  // GRAPHICS_VERTEXPOSITIONNORMALTEXTURE_HPP
