// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/TextureObject.hpp>

#include <System/Graphics/Platform.hpp>
#include <Graphics/Texture.hpp>

using namespace System;
using namespace SceneR::Graphics;

TextureObject::TextureObject(const TextureTarget& target)
    : texId  { 0 }
    , target { target }
{
    this->Create();
}

TextureObject::~TextureObject()
{
}

void TextureObject::Dispose()
{
    if (this->texId != 0)
    {
        glDeleteTextures(1, &this->texId);
        this->texId = 0;
    }
}

void TextureObject::Activate() const
{
    glBindTexture(static_cast<GLenum>(this->target), this->texId);
}

void TextureObject::Create()
{
    glGenTextures(1, &this->texId);
}

void TextureObject::Deactivate() const
{
    glBindTexture(static_cast<GLenum>(this->target), 0);
}

void TextureObject::Declare2DStorage(const SurfaceFormat& format
                                   , const uint32_t&      levels
                                   , const uint32_t&      width
                                   , const uint32_t&      height) const
{
    glTextureStorage2DEXT(this->texId
                        , static_cast<GLenum>(this->target)
                        , static_cast<GLint>(levels)
                        , static_cast<GLenum>(format)
                        , static_cast<GLint>(width)
                        , static_cast<GLint>(height));
}

void TextureObject::TextureSubImage2D(const SurfaceFormat& format
                                    , const uint32_t&      level
                                    , const uint32_t&      width
                                    , const uint32_t&      height
                                    , const size_t&        size
                                    , const void*          data) const
{
    if (Texture::IsCompressedSurfaceFormat(format))
    {
        glCompressedTextureSubImage2DEXT(this->texId
                                       , static_cast<GLenum>(this->target)
                                       , static_cast<GLint>(level)
                                       , 0
                                       , 0
                                       , static_cast<GLint>(width)
                                       , static_cast<GLint>(height)
                                       , static_cast<GLenum>(format)
                                       , size
                                       , data);
    }
    else
    {
        glTextureSubImage2DEXT(this->texId
                             , static_cast<GLenum>(this->target)
                             , static_cast<GLint>(level)
                             , 0
                             , 0
                             , static_cast<GLint>(width)
                             , static_cast<GLint>(height)
                             , static_cast<GLenum>(format)
                             , GL_UNSIGNED_BYTE
                             , data);
    }
}
