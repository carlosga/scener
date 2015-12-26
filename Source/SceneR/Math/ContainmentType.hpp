// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_MATH_CONTAINMENTTYPE_HPP
#define SCENER_MATH_CONTAINMENTTYPE_HPP

#include <cstdint>

namespace SceneR
{
    namespace Math
    {
        /**
         * Indicates the extent to which bounding volumes intersect or contain one another.
         */
        enum class ContainmentType : std::int32_t
        {
            /**
             * Indicates that one bounding volume completely contains the other.
             */
            Contains = 0,
            /**
             * Indicates there is no overlap between the bounding volumes.
             */
            Disjoint = 1,
            /**
             * Indicates that the bounding volumes partially overlap.
             */
            Intersects = 2
        };
    }
}

#endif // SCENER_MATH_CONTAINMENTTYPE_HPP
