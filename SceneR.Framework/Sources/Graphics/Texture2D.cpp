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
#include <Graphics/GraphicsDevice.hpp>
#include <Graphics/Texture2D.hpp>
#include <Graphics/TextureTarget.hpp>

using namespace System;
using namespace SceneR::Graphics;

Texture2D::Texture2D(GraphicsDevice& graphicsDevice,
                     const UInt32&   width,
                     const UInt32&   height)
    : Texture2D(graphicsDevice, width, height, false, SurfaceFormat::Color)
{
}

Texture2D::Texture2D(GraphicsDevice&      graphicsDevice,
                     const UInt32&        width,
                     const UInt32&        height,
                     const Boolean&       mipMap,
                     const SurfaceFormat& format)
    : Texture(graphicsDevice),
      format(format),
      height(height),
      mipmapLevels(0),
      mipmapHeight(height),
      mipmapWidth(width),
      width(width),
      object(width, height, format, TextureTarget::Texture2D)
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

const Int32 Texture2D::LevelCount() const
{
    return this->mipmapLevels;
}

const UInt32& Texture2D::Width() const
{
    return this->width;
}

void Texture2D::SetData(const UInt32& mipmapLevel, const Size& size, const void* data)
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

    this->object.TextureSubImage2D(this->format, mipmapLevel, this->mipmapWidth, this->mipmapHeight, size, data);

    this->mipmapWidth  >>= 1;
    this->mipmapHeight >>= 1;
}

void Texture2D::DeclareStorage(const System::UInt32& mipMapLevels) const
{
    this->object.DeclareStorage(this->format, mipMapLevels, this->width, this->height);
}

void Texture2D::Activate() const
{
    this->object.Activate();
}

void Texture2D::Deactivate() const
{
    this->object.Deactivate();
}
