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

#ifndef VERTEXPOSITIONNORMALTEXTURE_HPP
#define VERTEXPOSITIONNORMALTEXTURE_HPP

#include "Core/Core.hpp"
#include "Core/Vector2.hpp"
#include "Core/Vector3.hpp"
#include "Graphics/VertexDeclaration.hpp"

namespace SceneR
{
    namespace Graphics
    {
        /**
         * Describes a  vertex format  that contains position, normal data, and texture coordinates.
         */
        class VertexPositionNormalTexture
        {
        public:
            /**
             * Gets the vertex declaration
             */
            static const VertexDeclaration GetVertexDeclaration();

        public:
            /**
             * Initializes a new instance of the VertexPositionNormalTexture class
             * with the given position, normal and texture coordinates.
             */
            VertexPositionNormalTexture(const SceneR::Core::Vector3& position,
                                        const SceneR::Core::Vector3& normal,
                                        const SceneR::Core::Vector2& textureCoordinate);

        public:
            /**
             * Gets the vertex position
             */
            const SceneR::Core::Vector3& GetPosition() const;

            /**
             * Gets the vertex normal
             */
            const SceneR::Core::Vector3& GetNormal() const;

            /**
             * Gets the vertex texture coordinates
             */
            const SceneR::Core::Vector2& GetTextureCoordinate() const;

        private:
            SceneR::Core::Vector3 position;
            SceneR::Core::Vector3 normal;
            SceneR::Core::Vector2 textureCoordinate;
        };
    }
}

#endif  /* VERTEXPOSITIONNORMALTEXTURE_HPP */