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

#include <Framework/RenderTime.hpp>
#include <System/TimeSpan.hpp>

using namespace System;
using namespace SceneR::Framework;

RenderTime::RenderTime()
    : RenderTime(System::TimeSpan::Zero, System::TimeSpan::Zero, false)
{
}

RenderTime::RenderTime(const System::TimeSpan& totalRenderTime
                     , const System::TimeSpan& elapsedRenderTime)
    : RenderTime(totalRenderTime, elapsedRenderTime, false)
{
}

RenderTime::RenderTime(const System::TimeSpan& totalRenderTime
                     , const System::TimeSpan& elapsedRenderTime
                     , const System::Boolean&  isRunningSlowly)
    : totalRenderTime(totalRenderTime)
    , elapsedRenderTime(elapsedRenderTime)
    , isRunningSlowly(isRunningSlowly)
{
}

RenderTime::~RenderTime()
{
}

const System::TimeSpan& RenderTime::ElapsedRenderTime() const
{
    return this->elapsedRenderTime;
}

void RenderTime::ElapsedRenderTime(const System::TimeSpan& elapsedRenderTime)
{
    this->elapsedRenderTime = elapsedRenderTime;
}

const System::Boolean& RenderTime::IsRunningSlowly() const
{
    return this->isRunningSlowly;
}

void RenderTime::IsRunningSlowly(const System::Boolean& isRunningSlowly)
{
    this->isRunningSlowly = isRunningSlowly;
}

const System::TimeSpan& RenderTime::TotalRenderTime() const
{
    return this->totalRenderTime;
}

void RenderTime::TotalRenderTime(const System::TimeSpan& totalRenderTime)
{
    this->totalRenderTime = totalRenderTime;
}
