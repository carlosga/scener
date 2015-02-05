// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef VERTEXPOSITIONCOLORTEXTURE_HPP
#define VERTEXPOSITIONCOLORTEXTURE_HPP

#include <Framework/Color.hpp>
#include <Framework/Vector2.hpp>
#include <Framework/Vector3.hpp>

namespace SceneR
{
    namespace Graphics
    {
        class VertexDeclaration;

        /**
         * Describes a  vertex format  that contains position, color, and texture coordinates.
         */
        struct VertexPositionColorTexture
        {
        private:
            static const VertexDeclaration& Declaration;

        public:
            /**
             * Gets the vertex declaration.
             */
            static const VertexDeclaration& GetVertexDeclaration();

        public:
            /**
             * Initializes a new instance of the VertexPositionColorTexture class.
             *
             * @param position the vertex position
             * @param color the vertex color
             * @param textureCoordinate the vertex texture coordinates
             */
            VertexPositionColorTexture(const SceneR::Framework::Vector3& position
                                     , const SceneR::Framework::Color&   color
                                     , const SceneR::Framework::Vector2& textureCoordinate);


            /**
             * Releases all resources being used by this VertexPositionColorTexture.
             */
            ~VertexPositionColorTexture() = default;

        public:
            /**
             * Gets the vertex position
             */
            const SceneR::Framework::Vector3& Position() const;

            /**
             * Gets the vertex color
             */
            const SceneR::Framework::Color& Color() const;

            /**
             * Gets the vertex texture coordinates
             */
            const SceneR::Framework::Vector2& TextureCoordinate() const;

        private:
            SceneR::Framework::Vector3 position;
            SceneR::Framework::Color   color;
            SceneR::Framework::Vector2 textureCoordinate;
        };
    }
}

#endif  /* VERTEXPOSITIONCOLORTEXTURE_HPP */
