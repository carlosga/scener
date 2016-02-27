// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_STEPTIME_HPP
#define SCENER_GRAPHICS_STEPTIME_HPP

#include "scener/timespan.hpp"

namespace scener { namespace graphics {

/// Snapshot of the rendering timing state.
struct steptime final
{
public:
    /// Initializes a new instance of the RenderTime class.
    steptime() noexcept;

    /// Initializes a new instance of the RenderTime class.
    /// \param total_time the amount of render time since the start of the game.
    /// \param elapsed_time the amount of elapsed render time since the last update.
    steptime(const timespan& total_time, const timespan& elapsed_time) noexcept;

    /// Initializes a new instance of the RenderTime class.
    /// \param total_time the amount of render time since the start of the game.
    /// \param elapsed_time the amount of elapsed render time since the last update.
    /// \param running_slowly a value indicating that the render loop is taking longer than its target_elapsed_time.
    steptime(const timespan& total_time, const timespan& elapsed_time, bool running_slowly) noexcept;

public:
    /// Gets or sets the amount of elapsed render time since the last update.
    timespan total_render_time;

    /// Gets or sets a value indicating that the render loop is taking longer than its target_elapsed_time.
    timespan elapsed_render_time;

    /// Gets or sets the amount of render time since the start of the renderer.
    bool is_running_slowly;
};

}}

#endif // SCENER_GRAPHICS_STEPTIME_HPP
