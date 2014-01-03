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

#include <Graphics/Texture.hpp>
#include <Graphics/TextureObject.hpp>

using namespace System;
using namespace SceneR::Graphics;

TextureObject::TextureObject(const TextureTarget& target)
    : texId(0),
      target(target)
{
    this->Create();
}

TextureObject::~TextureObject()
{
    this->Delete();
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

void TextureObject::Delete()
{
    glDeleteTextures(1, &this->texId);
}

void TextureObject::Declare2DStorage(const SurfaceFormat& format,
                                     const UInt32&        mipMapLevels,
                                     const UInt32&        width,
                                     const UInt32&        height) const
{
    this->Activate();

    glTexStorage2D(static_cast<GLenum>(this->target),
                   mipMapLevels,
                   static_cast<GLenum>(format),
                   width,
                   height);

    this->Deactivate();
}

void TextureObject::TextureSubImage2D(const SurfaceFormat&  format,
                                      const System::UInt32& mipMapLevel,
                                      const UInt32&         width,
                                      const UInt32&         height,
                                      const Size&           size,
                                      const void*           data) const
{
    this->Activate();

    if (Texture::IsCompressedSurfaceFormat(format))
    {
        glCompressedTexSubImage2D(static_cast<GLenum>(this->target),
                                  mipMapLevel,
                                  0,
                                  0,
                                  width,
                                  height,
                                  static_cast<GLenum>(format),
                                  size,
                                  data);
    }
    else
    {
        glTexSubImage2D(static_cast<GLenum>(this->target),
                        mipMapLevel,
                        0,
                        0,
                        width,
                        height,
                        static_cast<GLenum>(format),
                        GL_UNSIGNED_BYTE,
                        data);
    }

    this->Deactivate();
}
