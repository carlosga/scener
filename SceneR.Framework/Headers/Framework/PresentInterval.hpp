// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the Apache License, Version 2.0. See LICENSE file in the project root for full license information.

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
