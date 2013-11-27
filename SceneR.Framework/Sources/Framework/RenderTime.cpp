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
#include <chrono>

using namespace System;
using namespace SceneR::Framework;

RenderTime::RenderTime()
    : totalRenderTime(System::Duration::zero()),
      elapsedRenderTime(System::Duration::zero())
{
}

SceneR::Framework::RenderTime::RenderTime(const System::Duration& totalRenderTime,
                                          const System::Duration& elapsedRenderTime)
    : totalRenderTime(totalRenderTime),
      elapsedRenderTime(elapsedRenderTime)
{
}

RenderTime::~RenderTime()
{
}

const System::Duration& RenderTime::ElapsedRenderTime() const
{
    return this->elapsedRenderTime;
}

const System::Duration& RenderTime::TotalRenderTime() const
{
    return this->totalRenderTime;
}

void RenderTime::ElapsedRenderTime(const System::Duration& elapsedRenderTime)
{
    this->elapsedRenderTime = elapsedRenderTime;
}

void RenderTime::TotalRenderTime(const System::Duration& totalRenderTime)
{
    this->totalRenderTime = totalRenderTime;
}