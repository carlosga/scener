// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/StepTime.hpp>

namespace SceneR
{
    namespace Graphics
    {
        using SceneR::TimeSpan;

        StepTime::StepTime()
            : StepTime { TimeSpan::zero, TimeSpan::zero, false }
        {
        }

        StepTime::StepTime(const TimeSpan& totalRenderTime, const TimeSpan& elapsedRenderTime)
            : StepTime { totalRenderTime, elapsedRenderTime, false }
        {
        }

        StepTime::StepTime(const TimeSpan& totalRenderTime
                         , const TimeSpan& elapsedRenderTime
                         , const bool&     isRunningSlowly)
            : total_render_time   { totalRenderTime }
            , elapsed_render_time { elapsedRenderTime }
            , is_running_slowly   { isRunningSlowly }
        {
        }
    }
}
