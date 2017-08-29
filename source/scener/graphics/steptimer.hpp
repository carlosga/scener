// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_STEPTIMER_HPP
#define SCENER_GRAPHICS_STEPTIMER_HPP

#include "scener/timespan.hpp"

namespace scener::graphics
{
    /// Step timer.
    class steptimer final
    {
    public:
        /// Initializes a new instance of the RendererTimer class.
        steptimer() = default;

    public:
        /// Resets the renderer time points.
        void reset() noexcept;

        /// Updates the last time step time point.
        void update_time_step() noexcept;

        /// Gets the time elapsed since the last timer reset.
        timespan elapsed_time() const noexcept;

        /// Gets the time elapsed since the last time step update.
        timespan elapsed_time_step_time() const noexcept;

    private:
        timespan::clock::time_point current_time() const noexcept;

    private:
        steptimer(const steptimer& timer) = delete;
        steptimer& operator=(const steptimer& timer) = delete;

    private:
        timespan::clock::time_point _start          { timespan::clock::now() };
        timespan::clock::time_point _last_time_step { timespan::clock::now() };
    };
}

#endif // SCENER_GRAPHICS_STEPTIMER_HPP
