// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Framework/RendererTimer.hpp>

namespace SceneR
{
    namespace Framework
    {
        using System::TimeSpan;

        void RendererTimer::reset()
        {
            _start          = current_time();
            _last_time_step = current_time();
        }

        void RendererTimer::update_time_step()
        {
            _last_time_step = current_time();
        }

        TimeSpan RendererTimer::elapsed_time() const
        {
            return TimeSpan::from_duration(current_time() - _start);
        }

        TimeSpan RendererTimer::elapsed_time_step_time() const
        {
            return TimeSpan::from_duration(current_time() - _last_time_step);
        }

        TimeSpan::clock::time_point RendererTimer::current_time() const
        {
            return TimeSpan::clock::now();
        }
    }
}
