// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/Viewport.hpp>

#include <cassert>

#include <System/Graphics/Platform.hpp>

using namespace System;
using namespace SceneR::Graphics;

Viewport::Viewport()
    : Viewport { 0.0f, 0.0f, 0.0f, 0.0f }
{
}

Viewport::Viewport(const Single& x    , const Single& y
                 , const Single& width, const Single& height)
    : Viewport { x, y, width, height, 0.0f, 1.0f }
{
}

Viewport::Viewport(const Single& x       , const Single& y
                 , const Single& width   , const Single& height
                 , const Single& minDepth, const Single& maxDepth)
    : x        { x }
    , y        { y }
    , width    { width }
    , height   { height }
    , minDepth { minDepth }
    , maxDepth { maxDepth }
{
}

const Single& Viewport::X() const
{
    return this->x;
}

const Single& Viewport::Y() const
{
    return this->y;
}

const Single& Viewport::Width() const
{
    return this->width;
}

const Single& Viewport::Height() const
{
    return this->height;
}

Single Viewport::AspectRatio() const
{
    assert(this->width > 0 && this->height > 0);

    return (this->width / this->height);
}

const Single& Viewport::MinDepth() const
{
    return this->minDepth;
}

void Viewport::MinDepth(const Single& minDepth)
{
    this->minDepth = minDepth;
}

const Single& Viewport::MaxDepth() const
{
    return this->maxDepth;
}

void Viewport::MaxDepth(const Single& maxDepth)
{
    this->maxDepth = maxDepth;
}

void Viewport::Update(const Single& width, const Single& height)
{
    this->Update(this->x, this->y, width, height);
}

void Viewport::Update(const Single& x, const Single& y, const Single& width, const Single& height)
{
    this->x      = x;
    this->x      = y;
    this->width  = width;
    this->height = height;

    this->Refresh();
}

void Viewport::Refresh() const
{
    glViewportIndexedf(0, this->x, this->y, this->width, this->height);
    glDepthRangeIndexed(0, this->minDepth, this->maxDepth);
}
