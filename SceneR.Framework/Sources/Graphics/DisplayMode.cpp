// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/DisplayMode.hpp>

#include <cassert>

using namespace System;
using namespace SceneR::Graphics;

DisplayMode::DisplayMode(const GLFWvidmode* mode)
    : aspectRatio { 0.0f }
    , format      { SurfaceFormat::Color }
    , height      ( mode->height )
    , width       ( mode->width )
{
    assert(mode->width != 0 && mode->height != 0);

    this->aspectRatio = static_cast<Single>(mode->width) / static_cast<Single>(mode->height);

    Int32 bitDepth = mode->redBits + mode->blueBits + mode->greenBits;

    switch (bitDepth)
    {
      case 16:
      case 8:
          this->format = SurfaceFormat::Bgr565;
          break;
    }
}

DisplayMode::DisplayMode(const DisplayMode& displayMode)
    : aspectRatio { displayMode.aspectRatio }
    , format      { displayMode.format }
    , height      ( displayMode.height )
    , width       ( displayMode.width )
{
}

const Single& DisplayMode::AspectRatio() const
{
    return this->aspectRatio;
}

const SurfaceFormat& DisplayMode::Format() const
{
    return this->format;
}

const Size& DisplayMode::Height() const
{
    return this->height;
}

const Size& DisplayMode::Width() const
{
    return this->width;
}

DisplayMode& DisplayMode::operator=(const DisplayMode& displayMode)
{
    if (this != &displayMode)
    {
        this->aspectRatio = displayMode.aspectRatio;
        this->format      = displayMode.format;
        this->height      = displayMode.height;
        this->width       = displayMode.width;
    }

    return *this;
}
