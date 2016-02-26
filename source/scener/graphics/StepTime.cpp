// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/StepTime.hpp"

namespace scener { namespace graphics {

using scener::time_span;

StepTime::StepTime() noexcept
    : StepTime { time_span::zero(), time_span::zero(), false }
{
}

StepTime::StepTime(const time_span& totalRenderTime, const time_span& elapsedRenderTime) noexcept
    : StepTime { totalRenderTime, elapsedRenderTime, false }
{
}

StepTime::StepTime(const time_span& totalRenderTime, const time_span& elapsedRenderTime, bool isRunningSlowly) noexcept
    : total_render_time   { totalRenderTime }
    , elapsed_render_time { elapsedRenderTime }
    , is_running_slowly   { isRunningSlowly }
{
}

}}
