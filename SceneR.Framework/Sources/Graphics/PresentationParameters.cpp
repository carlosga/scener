// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/PresentationParameters.hpp>

using namespace SceneR::Graphics;

PresentationParameters::PresentationParameters()
    : fullScreen       { false }
    , backBufferHeight { 0 }
    , backBufferWidth  { 0 }
    , multiSampleCount { 8 }
    , presentInterval  { SceneR::Framework::PresentInterval::Default }
{
}

PresentationParameters::PresentationParameters(const PresentationParameters& parameters)
    : fullScreen       { parameters.fullScreen }
    , backBufferHeight { parameters.backBufferHeight }
    , backBufferWidth  { parameters.backBufferWidth }
    , multiSampleCount { parameters.multiSampleCount }
    , presentInterval  { parameters.presentInterval }
{
}

PresentationParameters::~PresentationParameters()
{
}

bool PresentationParameters::FullScreen() const
{
    return this->fullScreen;
}

void PresentationParameters::FullScreen(const bool& fullScreen)
{
    this->fullScreen = fullScreen;
}

uint32_t PresentationParameters::BackBufferHeight() const
{
    return this->backBufferHeight;
}

void PresentationParameters::BackBufferHeight(const uint32_t& backBufferHeight)
{
    this->backBufferHeight = backBufferHeight;
}

uint32_t PresentationParameters::BackBufferWidth() const
{
    return this->backBufferWidth;
}

void PresentationParameters::BackBufferWidth(const uint32_t& backBufferWidth)
{
    this->backBufferWidth = backBufferWidth;
}

uint32_t PresentationParameters::MultiSampleCount() const
{
    return this->multiSampleCount;
}

void PresentationParameters::MultiSampleCount(const uint32_t& multiSampleCount)
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

PresentationParameters&PresentationParameters::operator=(const PresentationParameters& parameters)
{
    if (this != &parameters)
    {
        this->fullScreen       = parameters.fullScreen;
        this->backBufferHeight = parameters.backBufferHeight;
        this->backBufferWidth  = parameters.backBufferWidth;
        this->multiSampleCount = parameters.multiSampleCount;
        this->presentInterval  = parameters.presentInterval;
    }

    return *this;
}
