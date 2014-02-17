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

#ifndef VERTEXPOSITIONCOLOR_HPP
#define VERTEXPOSITIONCOLOR_HPP

#include <Framework/Color.hpp>
#include <Framework/Vector3.hpp>

namespace SceneR
{
    namespace Graphics
    {
        class VertexDeclaration;

        /**
         * Describes a custom vertex format structure that contains position and color information.
         */
        struct VertexPositionColor
        {
        private:
            static const VertexDeclaration& Declaration;

        public:
            /**
             * Vertex declaration, which defines per-vertex data.
             */
            static const VertexDeclaration& GetVertexDeclaration();

        public:
            /**
             * Initializes a new instance of the VertexPositionColor class with the
             * given position and color.
             */
            VertexPositionColor(const SceneR::Framework::Vector3& position
                              , const SceneR::Framework::Color& color);

            /**
             * Releases all resources being used by this VertexPositionColor.
             */
            ~VertexPositionColor() = default;

        public:
            /**
             * Gets the vertex position.
             */
            const SceneR::Framework::Vector3& Position() const;

            /**
             * Gets the vertex color.
             */
            const SceneR::Framework::Color& Color() const;

        private:
            SceneR::Framework::Vector3 position;
            SceneR::Framework::Color   color;
        };
    }
}

#endif  /* VERTEXPOSITIONCOLOR_HPP */
