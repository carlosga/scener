// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Framework/RendererTimer.hpp>

namespace SceneR
{
    namespace Framework
    {
        using System::TimeSpan;

        RendererTimer::RendererTimer()
            : start        { TimeSpan::Clock::now() }
            , lastTimeStep { TimeSpan::Clock::now() }
        {
        }

        RendererTimer::~RendererTimer()
        {
        }

        void RendererTimer::Reset()
        {
            this->start        = this->CurrentTime();
            this->lastTimeStep = this->CurrentTime();
        }

        void RendererTimer::UpdateTimeStep()
        {
            this->lastTimeStep = this->CurrentTime();
        }

        TimeSpan RendererTimer::ElapsedTime() const
        {
            return TimeSpan::FromDuration(this->CurrentTime() - this->start);
        }

        TimeSpan RendererTimer::ElapsedTimeStepTime() const
        {
            return TimeSpan::FromDuration(this->CurrentTime() - this->lastTimeStep);
        }

        TimeSpan::Clock::time_point RendererTimer::CurrentTime() const
        {
            return TimeSpan::Clock::now();
        }
    }
}
