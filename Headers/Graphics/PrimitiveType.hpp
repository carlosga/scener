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

#ifndef PRIMITIVETYPE_HPP
#define PRIMITIVETYPE_HPP

#include "Core/Core.hpp"

namespace SceneR
{
    namespace Graphics
    {
        /**
         * Defines the primitives types
         */
        enum class PrimitiveType : GLenum
        {
            /**
             * Renders the vertices as a collection of isolated points. This value is unsupported for indexed primitives.
             */
            PointList = GL_POINTS,
            /*
             * Renders the vertices as a list of isolated straight line segments. Calls that use this primitive type fail if the count is less than two or is odd.
             */
            LineList = GL_LINES,
            /*
             * Renders the vertices as a single polyline. Calls that use this primitive type fail if the count is less than two.
             */
            LineStrip = GL_LINE_STRIP,
            /**
             * Renders the specified vertices as a sequence of isolated triangles. Each group of three vertices defines a separate triangle. Back face culling is affected by the current winding-order render state.
             */
            TriangleList = GL_TRIANGLES,
            /**
             * Renders the vertices as a triangle strip. The back face culling flag is flipped automatically on even-numbered triangles.
             */
            TriangleStrip = GL_TRIANGLE_STRIP,
            /**
             * Renders the vertices as a triangle fan.
             */
            TriangleFan = GL_TRIANGLE_FAN
        };
    }
}

#endif /* PRIMITIVETYPE_HPP */
