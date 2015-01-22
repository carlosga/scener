// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the Apache License, Version 2.0. See LICENSE file in the project root for full license information.

#ifndef FILLMODE_HPP
#define FILLMODE_HPP

#include <System/Core.hpp>

namespace SceneR
{
    namespace Graphics
    {
        /**
         * Describes options for filling the vertices and lines that define a primitive.
         */
        enum class FillMode : System::UInt32
        {
            /**
             * Draw solid faces for each primitive.
             */
            Solid = 1,
            /**
             * Draw lines connecting the vertices that define a primitive face.
             */
            WireFrame = 2
        };
    }
}

#endif  /* FILLMODE_HPP */
