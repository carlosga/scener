// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_STEPTIME_HPP
#define SCENER_GRAPHICS_STEPTIME_HPP

#include "scener/timespan.hpp"

namespace scener { namespace graphics {

/// Snapshot of the rendering timing state.
struct StepTime final
{
public:
    /// Initializes a new instance of the RenderTime class.
    StepTime() noexcept;

    /// Initializes a new instance of the RenderTime class.
    /// \param totalRenderTime the amount of render time since the start of the game.
    /// \param elapsedRenderTime the amount of elapsed render time since the last update.
    StepTime(const scener::timespan& totalRenderTime, const scener::timespan& elapsedRenderTime) noexcept;

    /// Initializes a new instance of the RenderTime class.
    /// \param totalRenderTime the amount of render time since the start of the game.
    /// \param elapsedRenderTime the amount of elapsed render time since the last update.
    /// \param isRunningSlowly a value indicating that the render loop is taking longer than its target_elapsed_time.
    StepTime(const scener::timespan& totalRenderTime
           , const scener::timespan& elapsedRenderTime
           , bool                    isRunningSlowly) noexcept;

public:
    /// Gets or sets the amount of elapsed render time since the last update.
    scener::timespan total_render_time;

    /// Gets or sets a value indicating that the render loop is taking longer than its target_elapsed_time.
    scener::timespan elapsed_render_time;

    /// Gets or sets the amount of render time since the start of the renderer.
    bool is_running_slowly;
};

}}

#endif // SCENER_GRAPHICS_STEPTIME_HPP
