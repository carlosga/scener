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

#include <functional>
#include <iomanip>
#include <Framework/RendererTimer.hpp>

using namespace System;
using namespace SceneR::Framework;

RendererTimer::RendererTimer()
    : start(Clock::now()),
      lastTick(Clock::now())
{
}

RendererTimer::~RendererTimer()
{
    // TODO Auto-generated destructor stub
}

void RendererTimer::Reset()
{
    this->start    = Clock::now();
    this->lastTick = Clock::now();
}

void SceneR::Framework::RendererTimer::Tick()
{
    this->lastTick = this->CurrentTime();
}

Duration RendererTimer::ElapsedTime() const
{
    return this->CalculateDuration(this->start, this->CurrentTime());
}

Duration RendererTimer::ElapsedTickTime() const
{
    return this->CalculateDuration(this->lastTick, this->CurrentTime());
}

Clock::time_point RendererTimer::CurrentTime() const
{
    return Clock::now();
}

Duration RendererTimer::CalculateDuration(const System::Clock::time_point& t0,
                                          const System::Clock::time_point& t1) const
{
   return std::chrono::duration_cast<System::Duration>(t1 - t0);
}
