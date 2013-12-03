//-------------------------------------------------------------------------------
//Copyright 2013 Carlos Guzmán Álvarez
//
//Licensed under the Apache License, Version 2.0 (the "License");
//you may not use this file except in compliance with the License.
//You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//Unless required by applicable law or agreed to in writing, software
//distributed under the License is distributed on an "AS IS" BASIS,
//WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//See the License for the specific language governing permissions and
//limitations under the License.
//-------------------------------------------------------------------------------

#include <Framework/RendererTimer.hpp>

using namespace System;
using namespace SceneR::Framework;

RendererTimer::RendererTimer()
    : start(TimeSpan::Clock::now()),
      lastTimeStep(TimeSpan::Clock::now())
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

void SceneR::Framework::RendererTimer::UpdateTimeStep()
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
