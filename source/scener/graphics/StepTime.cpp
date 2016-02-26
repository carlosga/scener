// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/StepTime.hpp"

namespace scener { namespace graphics {

using scener::timespan;

StepTime::StepTime() noexcept
    : StepTime { timespan::zero(), timespan::zero(), false }
{
}

StepTime::StepTime(const timespan& totalRenderTime, const timespan& elapsedRenderTime) noexcept
    : StepTime { totalRenderTime, elapsedRenderTime, false }
{
}

StepTime::StepTime(const timespan& totalRenderTime, const timespan& elapsedRenderTime, bool isRunningSlowly) noexcept
    : total_render_time   { totalRenderTime }
    , elapsed_render_time { elapsedRenderTime }
    , is_running_slowly   { isRunningSlowly }
{
}

}}
