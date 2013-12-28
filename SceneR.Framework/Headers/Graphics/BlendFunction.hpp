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

#ifndef BLENDFUNCTION_HPP
#define BLENDFUNCTION_HPP

namespace SceneR
{
    namespace Graphics
    {
        /**
         * Defines how to combine a source color with the destination color already on the render target for color blending.
         */
        enum class BlendFunction : System::UInt32
        {
            /**
             * The result is the destination added to the source.
             * Result = (Source Color * Source Blend) + (Destination Color * Destination Blend)
             */
            Add,
            /**
             * The result is the maximum of the source and destination.
             * Result = max( (Source Color * Source Blend), (Destination Color * Destination Blend) )
             */
            Max,
            /**
             * The result is the minimum of the source and destination.
             * Result = min( (Source Color * Source Blend), (Destination Color * Destination Blend) )
             */
            Min,
            /**
             * The result is the source subtracted from the destination.
             * Result = (Destination Color * Destination Blend) − (Source Color * Source Blend)
             */
            ReverseSubtract,
            /**
             * The result is the destination subtracted from the source.
             * Result = (Source Color * Source Blend) − (Destination Color * Destination Blend)
             */
            Subtract
        };
    }
}

#endif /* BLENDFUNCTION_HPP */
