// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/PresentationParameters.hpp>

using namespace System;
using namespace SceneR::Graphics;

PresentationParameters::PresentationParameters()
    : fullScreen       { false }
    , backBufferHeight { 0 }
    , backBufferWidth  { 0 }
    , multiSampleCount { 8 }
    , presentInterval  { SceneR::Framework::PresentInterval::Default }
{
}

PresentationParameters::~PresentationParameters()
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
