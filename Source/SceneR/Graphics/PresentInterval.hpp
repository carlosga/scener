// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_PRESENTINTERVAL_HPP
#define SCENER_GRAPHICS_PRESENTINTERVAL_HPP

#include <cstdint>

namespace SceneR { namespace Graphics {

/**
 * Defines flags that describe the relationship between the adapter refresh rate and
 * the rate at which Present operations are completed.
 */
enum class PresentInterval : std::uint32_t
{
    /**
     * The driver waits for the vertical retrace period (the runtime will beam trace to prevent tearing).
     */
    one = 1,
    /**
     * The driver waits for the vertical retrace period.
     */
    two = 2,
    /**
     * The runtime updates the window client area immediately.
     */
    immediate = 3
};

}}

#endif // SCENER_GRAPHICS_PRESENTINTERVAL_HPP
