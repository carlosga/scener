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

#include <Graphics/Viewport.hpp>
#include <System/Graphics/Platform.hpp>
#include <cassert>

using namespace System;
using namespace SceneR::Graphics;

Viewport::Viewport()
    : Viewport(0.0f, 0.0f, 0.0f, 0.0f)
{
}

Viewport::Viewport(const Single& x, const Single& y, const Size& width, const Size& height)
    : Viewport(x, y, width, height, 0.0f, 1.0f)
{
}

Viewport::Viewport(const Single& x    , const Single& y
                 , const Single& width, const Single& height
                 , const Single& minDepth, const Single& maxDepth)
    : x(x)
    , y(y)
    , width(width)
    , height(height)
    , minDepth(minDepth)
    , maxDepth(maxDepth)
{
}

Viewport::~Viewport()
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

void Viewport::Update(const Size& width, const Size& height)
{
    this->Update(this->x, this->y, width, height);
}

void Viewport::Update(const UInt32& x, const UInt32& y, const Size& width, const Size& height)
{
    this->x = x;
    this->x = y;
    this->width      = width;
    this->height     = height;

    this->Refresh();
}

void Viewport::Refresh() const
{
    glViewportIndexedf(0, this->x, this->y, this->width, this->height);
    glDepthRangeIndexed(0, this->minDepth, this->maxDepth);
}
