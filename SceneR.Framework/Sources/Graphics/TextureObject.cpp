// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <Graphics/TextureObject.hpp>

#include <System/Graphics/Platform.hpp>
#include <Graphics/Texture.hpp>

namespace SceneR
{
    namespace Graphics
    {
        TextureObject::TextureObject(const TextureTarget& target) noexcept
            : _id     { 0 }
            , _target { target }
        {
            create();
        }

        void TextureObject::dispose()
        {
            if (_id != 0)
            {
                glDeleteTextures(1, &_id);
                _id = 0;
            }
        }

        std::uint32_t TextureObject::id() const noexcept
        {
            return _id;
        }

        void TextureObject::bind() const
        {
            glBindTextureUnit(0, _id);
        }

        void TextureObject::create()
        {
            glCreateTextures(static_cast<GLenum>(_target), 1, &_id);
        }

        void TextureObject::unbind() const
        {
            glBindTextureUnit(0, 0);
        }

        void TextureObject::declare_2D_storage(const SurfaceFormat& format
                                             , const std::size_t&   levels
                                             , const std::size_t&   width
                                             , const std::size_t&   height) const
        {
            glTextureStorage2D(_id
                             , static_cast<GLint>(levels)
                             , static_cast<GLenum>(format)
                             , static_cast<GLint>(width)
                             , static_cast<GLint>(height));
        }

        void TextureObject::texture_sub_image_2D(const SurfaceFormat&             format
                                               , const std::size_t&               level
                                               , const std::size_t&               width
                                               , const std::size_t&               height
                                               , const std::vector<std::uint8_t>& data) const
        {
            auto si_level  = static_cast<GLint>(level);
            auto si_width  = static_cast<GLint>(width);
            auto si_height = static_cast<GLint>(height);
            auto si_format = static_cast<GLenum>(format);

            if (Texture::is_compressed_surface_format(format))
            {
                glCompressedTextureSubImage2D(_id, si_level, 0, 0, si_width, si_height, si_format, data.size(), data.data());
            }
            else
            {
                glTextureSubImage2D(_id, si_level, 0, 0, si_width, si_height, si_format, GL_UNSIGNED_BYTE, data.data());
            }
        }
    }
}
