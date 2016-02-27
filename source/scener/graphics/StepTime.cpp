// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/StepTime.hpp"

namespace scener { namespace graphics {

using scener::timespan;

steptime::steptime() noexcept
    : steptime { timespan::zero(), timespan::zero(), false }
{
}

steptime::steptime(const timespan& total_time, const timespan& elapsed_time) noexcept
    : steptime { total_time, elapsed_time, false }
{
}

steptime::steptime(const timespan& total_time, const timespan& elapsed_time, bool running_slowly) noexcept
    : total_render_time   { total_time }
    , elapsed_render_time { elapsed_time }
    , is_running_slowly   { running_slowly }
{
}

}}
