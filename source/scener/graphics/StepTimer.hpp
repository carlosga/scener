// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_STEPTIMER_HPP
#define SCENER_GRAPHICS_STEPTIMER_HPP

#include "scener/timespan.hpp"

namespace scener { namespace graphics {

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
    scener::timespan elapsed_time() const noexcept;

    /// Gets the time elapsed since the last time step update.
    scener::timespan elapsed_time_step_time() const noexcept;

private:
    scener::timespan::clock::time_point current_time() const noexcept;

private:
    steptimer(const steptimer& timer) = delete;
    steptimer& operator=(const steptimer& timer) = delete;

private:
    scener::timespan::clock::time_point _start          { scener::timespan::clock::now() };
    scener::timespan::clock::time_point _last_time_step { scener::timespan::clock::now() };
};

}}

#endif // SCENER_GRAPHICS_STEPTIMER_HPP
