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

#ifndef PRESENTINTERVAL_HPP
#define PRESENTINTERVAL_HPP

#include <System/Core.hpp>

namespace SceneR
{
    namespace Framework
    {
        /**
         * Defines flags that describe the relationship between the adapter refresh rate and
         * the rate at which Present operations are completed.
         */
        enum class PresentInterval : System::Int32
        {
            /**
             * Equivalent to setting One.
             */
            Default = 1,
            /**
             * The driver waits for the vertical retrace period (the runtime will beam trace to prevent tearing).
             */
            One = 2,
            /**
             * The driver waits for the vertical retrace period.
             */
            Two = 3,
            /**
             * The runtime updates the window client area immediately.
             */
            Immediate = 4
        };
    }
}

#endif /* PRESENTINTERVAL_HPP */
