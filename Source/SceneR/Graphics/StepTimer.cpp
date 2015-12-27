// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "StepTimer.hpp"

namespace SceneR
{
    namespace Graphics
    {
        using SceneR::TimeSpan;

        void StepTimer::reset() noexcept
        {
            _start          = current_time();
            _last_time_step = current_time();
        }

        void StepTimer::update_time_step() noexcept
        {
            _last_time_step = current_time();
        }

        TimeSpan StepTimer::elapsed_time() const noexcept
        {
            return TimeSpan::from_duration(current_time() - _start);
        }

        TimeSpan StepTimer::elapsed_time_step_time() const noexcept
        {
            return TimeSpan::from_duration(current_time() - _last_time_step);
        }

        TimeSpan::clock::time_point StepTimer::current_time() const noexcept
        {
            return TimeSpan::clock::now();
        }
    }
}
