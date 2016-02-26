// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/StepTimer.hpp"

namespace scener { namespace graphics {

using scener::time_span;

void StepTimer::reset() noexcept
{
    _start          = current_time();
    _last_time_step = current_time();
}

void StepTimer::update_time_step() noexcept
{
    _last_time_step = current_time();
}

time_span StepTimer::elapsed_time() const noexcept
{
    return time_span::from_duration(current_time() - _start);
}

time_span StepTimer::elapsed_time_step_time() const noexcept
{
    return time_span::from_duration(current_time() - _last_time_step);
}

time_span::clock::time_point StepTimer::current_time() const noexcept
{
    return time_span::clock::now();
}

}}
