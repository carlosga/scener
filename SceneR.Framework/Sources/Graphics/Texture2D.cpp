// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/Texture2D.hpp>

#include <Graphics/GraphicsDevice.hpp>

using namespace System;
using namespace SceneR::Graphics;

Texture2D::Texture2D(GraphicsDevice& graphicsDevice
                   , const UInt32&   width
                   , const UInt32&   height)
    : Texture2D(graphicsDevice, width, height, false, SurfaceFormat::Color)
{
}

Texture2D::Texture2D(GraphicsDevice&      graphicsDevice
                   , const UInt32&        width
                   , const UInt32&        height
                   , const Boolean&       mipmap
                   , const SurfaceFormat& format)
    : Texture      { graphicsDevice }
    , format       { format }
    , height       { height }
    , mipmap       { mipmap }
    , mipmapLevels { 0 }
    , mipmapHeight { height }
    , mipmapWidth  { width }
    , width        { width }
    , object       { TextureTarget::Texture2D }
{
}

Texture2D::~Texture2D()
{
}

const SurfaceFormat& Texture2D::Format() const
{
    return this->format;
}

const UInt32& Texture2D::Height() const
{
    return this->height;
}

const UInt32& Texture2D::LevelCount() const
{
    return this->mipmapLevels;
}

const UInt32& Texture2D::Width() const
{
    return this->width;
}

void Texture2D::SetData(const UInt32& level, const Size& size, const void* data)
{
    // http://www.oldunreal.com/editing/s3tc/ARB_texture_compression.pdf
    if (this->mipmapWidth == 0)
    {
        this->mipmapWidth = 1;
    }
    if (this->mipmapHeight == 0)
    {
        this->mipmapHeight = 1;
    }

    this->object.TextureSubImage2D(this->format, level, this->mipmapWidth, this->mipmapHeight, size, data);

    this->mipmapWidth  >>= 1;
    this->mipmapHeight >>= 1;
}

void Texture2D::DeclareStorage(const UInt32& mipMapLevels)
{
    this->object.Declare2DStorage(this->format, mipMapLevels, this->width, this->height);
    this->mipmapLevels = mipMapLevels;
}

void Texture2D::Activate()
{
    this->object.Activate();
}

void Texture2D::Deactivate()
{
    this->object.Deactivate();
}
