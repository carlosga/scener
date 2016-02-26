// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_STEPTIMER_HPP
#define SCENER_GRAPHICS_STEPTIMER_HPP

#include "scener/TimeSpan.hpp"

namespace scener { namespace graphics {

/// Step timer.
class StepTimer final
{
public:
    /// Initializes a new instance of the RendererTimer class.
    StepTimer() = default;

public:
    /// Resets the renderer time points.
    void reset() noexcept;

    /// Updates the last time step time point.
    void update_time_step() noexcept;

    /// Gets the time elapsed since the last timer reset.
    scener::time_span elapsed_time() const noexcept;

    /// Gets the time elapsed since the last time step update.
    scener::time_span elapsed_time_step_time() const noexcept;

private:
    scener::time_span::clock::time_point current_time() const noexcept;

private:
    StepTimer(const StepTimer& timer) = delete;
    StepTimer& operator=(const StepTimer& timer) = delete;

private:
    scener::time_span::clock::time_point _start          { scener::time_span::clock::now() };
    scener::time_span::clock::time_point _last_time_step { scener::time_span::clock::now() };
};

}}

#endif // SCENER_GRAPHICS_STEPTIMER_HPP
