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

#include <Graphics/PresentationParameters.hpp>

using namespace System;
using namespace SceneR::Graphics;

PresentationParameters::PresentationParameters()
    : fullScreen(false)
    , backBufferHeight(0)
    , backBufferWidth(0)
    , multiSampleCount(8)
    , presentInterval(SceneR::Framework::PresentInterval::Default)
{
}

const Boolean& PresentationParameters::FullScreen() const
{
    return this->fullScreen;
}

void PresentationParameters::FullScreen(const Boolean& fullScreen)
{
    this->fullScreen = fullScreen;
}

const Size& PresentationParameters::BackBufferHeight() const
{
    return this->backBufferHeight;
}

void PresentationParameters::BackBufferHeight(const Size& backBufferHeight)
{
    this->backBufferHeight = backBufferHeight;
}

const Size& PresentationParameters::BackBufferWidth() const
{
    return this->backBufferWidth;
}

void PresentationParameters::BackBufferWidth(const Size& backBufferWidth)
{
    this->backBufferWidth = backBufferWidth;
}

const System::Size& PresentationParameters::MultiSampleCount() const
{
    return this->multiSampleCount;
}

void PresentationParameters::MultiSampleCount(const System::Size& multiSampleCount)
{
    this->multiSampleCount = multiSampleCount;
}

const SceneR::Framework::PresentInterval& PresentationParameters::PresentInterval() const
{
    return presentInterval;
}

void PresentationParameters::PresentInterval(const SceneR::Framework::PresentInterval& presentInterval)
{
    this->presentInterval = presentInterval;
}
