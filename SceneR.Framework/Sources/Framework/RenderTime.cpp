// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Framework/RenderTime.hpp>

namespace SceneR
{
    namespace Framework
    {
        using System::TimeSpan;

        RenderTime::RenderTime()
            : RenderTime { TimeSpan::zero, TimeSpan::zero, false }
        {
        }

        RenderTime::RenderTime(const TimeSpan& totalRenderTime, const TimeSpan& elapsedRenderTime)
            : RenderTime { totalRenderTime, elapsedRenderTime, false }
        {
        }

        RenderTime::RenderTime(const TimeSpan& totalRenderTime
                             , const TimeSpan& elapsedRenderTime
                             , const bool&     isRunningSlowly)
            : total_render_time   { totalRenderTime }
            , elapsed_render_time { elapsedRenderTime }
            , is_running_slowly   { isRunningSlowly }
        {
        }

        RenderTime::~RenderTime()
        {
        }
    }
}
