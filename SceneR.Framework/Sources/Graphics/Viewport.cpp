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

#include <GL/glew.h>
#include <Graphics/Viewport.hpp>

using namespace System;
using namespace SceneR::Graphics;

Viewport::Viewport()
    : Viewport(0.0f, 0.0f, 0.0f, 0.0f)
{
}

Viewport::Viewport(Single x, Single y, Size width, Size height)
    : Viewport(x, y, width, height, 0.0f, 1.0f)
{
}

Viewport::Viewport(Single x , Single y, Single width, Single height, Single minDepth, Single maxDepth)
    : xCoordinate(x), yCoordinate(y), vWidth(width), vHeight(height), minDepth(minDepth), maxDepth(maxDepth)
{
}

Viewport::~Viewport()
{
}

const Single& Viewport::X() const
{
    return this->xCoordinate;
}

const Single& Viewport::Y() const
{
    return this->yCoordinate;
}

const Single& Viewport::Width() const
{
    return this->vWidth;
}

const Single& Viewport::Height() const
{
    return this->vHeight;
}

Single Viewport::AspectRatio() const
{
    return (this->vWidth / this->vHeight);
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
    this->Update(this->xCoordinate, this->yCoordinate, width, height);
}

void Viewport::Update(const UInt32& x, const UInt32& y, const Size& width, const Size& height)
{
    this->xCoordinate = x;
    this->xCoordinate = y;
    this->vWidth      = width;
    this->vHeight     = height;

    this->Refresh();
}

void Viewport::Refresh() const
{
    glViewport(this->xCoordinate, this->yCoordinate, this->vWidth, this->vHeight);
}
