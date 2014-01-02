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

#ifndef STENCILOPERATION_HPP
#define STENCILOPERATION_HPP

#include <System/Core.hpp>
#include <System/Graphics/Platform.hpp>

namespace SceneR
{
    namespace Graphics
    {
        /**
         * Defines stencil buffer operations.
         */
        enum class StencilOperation : System::UInt32
        {
            /**
             * Decrements the stencil-buffer entry, wrapping to the maximum value if the new value is less than 0.
             */
            Decrement = GL_DECR,
            /**
             * Decrements the stencil-buffer entry, clamping to 0.
             */
            DecrementSaturation = GL_DECR_WRAP,
            /**
             * Increments the stencil-buffer entry, wrapping to 0 if the new value exceeds the maximum value.
             */
            Increment = GL_INCR,
            /**
             * Increments the stencil-buffer entry, clamping to the maximum value.
             */
            IncrementSaturation = GL_INCR_WRAP,
            /**
             * Inverts the bits in the stencil-buffer entry.
             */
            Invert = GL_INVERT,
            /**
             * Does not update the stencil-buffer entry. This is the default value.
             */
            Keep = GL_KEEP,
            /**
             * Replaces the stencil-buffer entry with a reference value.
             */
            Replace = GL_REPLACE,
            /**
             * Sets the stencil-buffer entry to 0.
             */
            Zero = GL_ZERO
        };
    }
}

#endif /* STENCILOPERATION_HPP */
