// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/StepTimer.hpp"

namespace scener { namespace graphics {

using scener::timespan;

void StepTimer::reset() noexcept
{
    _start          = current_time();
    _last_time_step = current_time();
}

void StepTimer::update_time_step() noexcept
{
    _last_time_step = current_time();
}

timespan StepTimer::elapsed_time() const noexcept
{
    return timespan::from_duration(current_time() - _start);
}

timespan StepTimer::elapsed_time_step_time() const noexcept
{
    return timespan::from_duration(current_time() - _last_time_step);
}

timespan::clock::time_point StepTimer::current_time() const noexcept
{
    return timespan::clock::now();
}

}}
