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
        always        = 0x0207  ///< Always passes.
      , equal         = 0x0202  ///< Passes if the incoming depth value is equal to the stored depth value.
      , greater       = 0x0204  ///< Passes if the incoming depth value is greater than the stored depth value.
      , greater_equal = 0x0206  ///< Passes if the incoming depth value is greater than or equal to the stored depth value.
      , less          = 0x0201  ///< Passes if the incoming depth value is less than the stored depth value.
      , less_equal    = 0x0203  ///< Passes if the incoming depth value is less than or equal to the stored depth value.
      , never         = 0x0200  ///< Never passes.
      , not_equal     = 0x0205  ///< Passes if the incoming depth value is not equal to the stored depth value.
    };
}

#endif // SCENER_GRAPHICS_COMPARE_FUNCTION_HPP
