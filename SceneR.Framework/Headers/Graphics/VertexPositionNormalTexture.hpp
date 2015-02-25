// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef VERTEXPOSITIONNORMALTEXTURE_HPP
#define VERTEXPOSITIONNORMALTEXTURE_HPP

#include <Framework/Vector2.hpp>
#include <Framework/Vector3.hpp>

namespace SceneR
{
    namespace Graphics
    {
        class VertexDeclaration;

        /**
         * Describes a  vertex format  that contains position, normal data, and texture coordinates.
         */
        struct VertexPositionNormalTexture
        {
        private:
            static const VertexDeclaration& Declaration;

        public:
            /**
             * Gets the vertex declaration
             */
            static const VertexDeclaration& GetVertexDeclaration();

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

        public:
            /**
             * Gets the vertex position
             */
            const SceneR::Framework::Vector3& Position() const;

            /**
             * Gets the vertex normal
             */
            const SceneR::Framework::Vector3& Normal() const;

            /**
             * Gets the vertex texture coordinates
             */
            const SceneR::Framework::Vector2& TextureCoordinate() const;

        private:
            SceneR::Framework::Vector3 position;
            SceneR::Framework::Vector3 normal;
            SceneR::Framework::Vector2 textureCoordinate;
        };
    }
}

#endif  /* VERTEXPOSITIONNORMALTEXTURE_HPP */
