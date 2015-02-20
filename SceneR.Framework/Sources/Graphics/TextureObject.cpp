// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/TextureObject.hpp>

#include <Graphics/Texture.hpp>

using namespace System;
using namespace SceneR::Graphics;

TextureObject::TextureObject(const TextureTarget& target)
    : texId  { 0 }
    , target { target }
{
    this->Create();
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
    // glActiveTexture(GL_TEXTURE0);
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
                                   , const UInt32&        levels
                                   , const UInt32&        width
                                   , const UInt32&        height) const
{
    glTextureStorage2DEXT(this->texId
                        , static_cast<GLenum>(this->target)
                        , levels
                        , static_cast<GLenum>(format)
                        , width
                        , height);
}

void TextureObject::TextureSubImage2D(const SurfaceFormat&  format
                                    , const System::UInt32& level
                                    , const UInt32&         width
                                    , const UInt32&         height
                                    , const Size&           size
                                    , const void*           data) const
{
    if (Texture::IsCompressedSurfaceFormat(format))
    {
        glCompressedTextureSubImage2DEXT(this->texId
                                       , static_cast<GLenum>(this->target)
                                       , level
                                       , 0
                                       , 0
                                       , width
                                       , height
                                       , static_cast<GLenum>(format)
                                       , size
                                       , data);
    }
    else
    {
        glTextureSubImage2DEXT(this->texId
                             , static_cast<GLenum>(this->target)
                             , level
                             , 0
                             , 0
                             , width
                             , height
                             , static_cast<GLenum>(format)
                             , GL_UNSIGNED_BYTE
                             , data);
    }
}
