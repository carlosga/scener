// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Framework/RenderTime.hpp>

using namespace System;
using namespace SceneR::Framework;

RenderTime::RenderTime()
    : RenderTime { TimeSpan::Zero, TimeSpan::Zero, false }
{
}

RenderTime::RenderTime(const TimeSpan& totalRenderTime
                     , const TimeSpan& elapsedRenderTime)
    : RenderTime { totalRenderTime, elapsedRenderTime, false }
{
}

RenderTime::RenderTime(const TimeSpan& totalRenderTime
                     , const TimeSpan& elapsedRenderTime
                     , const bool&     isRunningSlowly)
    : totalRenderTime   { totalRenderTime }
    , elapsedRenderTime { elapsedRenderTime }
    , isRunningSlowly   { isRunningSlowly }
{
}

RenderTime::~RenderTime()
{
}

const TimeSpan& RenderTime::ElapsedRenderTime() const
{
    return this->elapsedRenderTime;
}

void RenderTime::ElapsedRenderTime(const TimeSpan& elapsedRenderTime)
{
    this->elapsedRenderTime = elapsedRenderTime;
}

bool RenderTime::IsRunningSlowly() const
{
    return this->isRunningSlowly;
}

void RenderTime::IsRunningSlowly(const bool& isRunningSlowly)
{
    this->isRunningSlowly = isRunningSlowly;
}

const TimeSpan& RenderTime::TotalRenderTime() const
{
    return this->totalRenderTime;
}

void RenderTime::TotalRenderTime(const TimeSpan& totalRenderTime)
{
    this->totalRenderTime = totalRenderTime;
}
