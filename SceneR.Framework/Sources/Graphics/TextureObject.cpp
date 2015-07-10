// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/TextureObject.hpp>

#include <System/Graphics/Platform.hpp>
#include <Graphics/Texture.hpp>

namespace SceneR
{
    namespace Graphics
    {
        TextureObject::TextureObject(const TextureTarget& target)
            : id  { 0 }
            , target { target }
        {
            this->Create();
        }

        TextureObject::~TextureObject()
        {
        }

        void TextureObject::Dispose()
        {
            if (this->id != 0)
            {
                glDeleteTextures(1, &this->id);
                this->id = 0;
            }
        }

        void TextureObject::Activate() const
        {
            glBindTexture(static_cast<GLenum>(this->target), this->id);
        }

        void TextureObject::Create()
        {
            glGenTextures(1, &this->id);
        }

        void TextureObject::Deactivate() const
        {
            glBindTexture(static_cast<GLenum>(this->target), 0);
        }

        void TextureObject::Declare2DStorage(const SurfaceFormat& format
                                           , const std::size_t&   levels
                                           , const std::size_t&   width
                                           , const std::size_t&   height) const
        {
            glTextureStorage2DEXT(this->id
                                , static_cast<GLenum>(this->target)
                                , static_cast<GLint>(levels)
                                , static_cast<GLenum>(format)
                                , static_cast<GLint>(width)
                                , static_cast<GLint>(height));
        }

        void TextureObject::TextureSubImage2D(const SurfaceFormat& format
                                            , const std::size_t&   level
                                            , const std::size_t&   width
                                            , const std::size_t&   height
                                            , const std::size_t&   size
                                            , const void*          data) const
        {
            if (Texture::IsCompressedSurfaceFormat(format))
            {
                glCompressedTextureSubImage2DEXT(this->id
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
                glTextureSubImage2DEXT(this->id
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
    }
}
