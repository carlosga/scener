// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_COMPARE_FUNCTION_HPP
#define SCENER_GRAPHICS_COMPARE_FUNCTION_HPP

#include <cstdint>

namespace scener::graphics
{
    /// Specifies the functions used to compare each incoming pixel depth value
    /// with the depth value present in the depth buffer.
    enum class compare_function : std::uint32_t
    {
        never         = 0  ///< Never passes.
      , less          = 1  ///< Passes if the incoming depth value is less than the stored depth value.
      , equal         = 2  ///< Passes if the incoming depth value is equal to the stored depth value.
      , less_equal    = 3  ///< Passes if the incoming depth value is less than or equal to the stored depth value.
      , greater       = 4  ///< Passes if the incoming depth value is greater than the stored depth value.
      , not_equal     = 5  ///< Passes if the incoming depth value is not equal to the stored depth value.
      , greater_equal = 6  ///< Passes if the incoming depth value is greater than or equal to the stored depth value.
      , always        = 7  ///< Always passes.
    };
}

#endif // SCENER_GRAPHICS_COMPARE_FUNCTION_HPP
