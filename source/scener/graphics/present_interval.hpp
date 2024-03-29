// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_PRESENT_INTERVAL_HPP
#define SCENER_GRAPHICS_PRESENT_INTERVAL_HPP

#include <cstdint>

namespace scener::graphics
{
    /// Defines flags that describe the relationship between the adapter refresh rate and
    /// the rate at which Present operations are completed.
    enum class present_interval : std::uint32_t
    {
        one       = 1 ///< The driver waits for the vertical retrace period (the runtime will beam trace to prevent tearing).
      , two       = 2 ///< The driver waits for the vertical retrace period.
      , immediate = 3 ///< The runtime updates the window client area immediately.
    };
}

#endif // SCENER_GRAPHICS_PRESENT_INTERVAL_HPP
