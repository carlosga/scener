// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/GraphicsResource.hpp>

using namespace System;
using namespace SceneR::Graphics;

GraphicsResource::GraphicsResource(GraphicsDevice& graphicsDevice)
    : graphicsDevice ( graphicsDevice )
    , name           { u""  }
    , tag            { u""  }
{
}

GraphicsResource::~GraphicsResource()
{
}

GraphicsDevice& GraphicsResource::CurrentGraphicsDevice()
{
    return this->graphicsDevice;
}

const String& GraphicsResource::Name() const
{
    return this->name;
}

void GraphicsResource::Name(const String& name)
{
    this->name = name;
}

const String& GraphicsResource::Tag() const
{
    return this->tag;
}

void GraphicsResource::Tag(const String& tag)
{
    this->tag = tag;
}
