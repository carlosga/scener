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
