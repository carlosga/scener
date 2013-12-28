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

#ifndef COLORWRITECHANNELS_HPP
#define COLORWRITECHANNELS_HPP

#include <System/Core.hpp>

namespace SceneR
{
    namespace Graphics
    {
        enum class ColorWriteChannels : System::UInt32
        {
            /**
             * All buffer channels.
             */
            All = 1,
            /**
             * Alpha channel of a buffer.
             */
            Alpha = 2,
            /**
             * Blue channel of a buffer.
             */
            Blue = 4,
            /**
             * Green channel of a buffer.
             */
            Green = 8,
            /**
             * No channel selected.
             */
            None = 0,
            /**
             * Red channel of a buffer.
             */
            Red = 16
        };
    }
}

#endif /* COLORWRITECHANNELS_HPP */
