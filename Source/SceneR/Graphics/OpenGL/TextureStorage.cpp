// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SceneR/Graphics/OpenGL/TextureStorage.hpp"

#include "SceneR/Graphics/SurfaceFormat.hpp"

namespace SceneR { namespace Graphics { namespace OpenGL {

TextureStorage::TextureStorage(TextureTarget target) noexcept
    : _id     { 0 }
    , _target { target }
{
    create();
}

TextureStorage::~TextureStorage() noexcept
{
    if (_id != 0)
    {
        glDeleteTextures(1, &_id);
        _id = 0;
    }
}

std::uint32_t TextureStorage::id() const noexcept
{
    return _id;
}

void TextureStorage::bind() const noexcept
{
    glBindTextureUnit(0, _id);
}

void TextureStorage::unbind() const noexcept
{
    glBindTextureUnit(0, 0);
}

void TextureStorage::declare_storage(SurfaceFormat format
                                   , std::size_t   levels
                                   , std::size_t   width
                                   , std::size_t   height) const noexcept
{
    glTextureStorage2D(_id
                     , static_cast<GLint>(levels)
                     , static_cast<GLenum>(format)
                     , static_cast<GLint>(width)
                     , static_cast<GLint>(height));
}

void TextureStorage::set_data(SurfaceFormat                        format
                            , std::size_t                          level
                            , std::size_t                          width
                            , std::size_t                          height
                            , const gsl::span<const std::uint8_t>& data) const noexcept
{
    auto si_level  = static_cast<GLint>(level);
    auto si_width  = static_cast<GLint>(width);
    auto si_height = static_cast<GLint>(height);
    auto si_format = static_cast<GLenum>(format);

    if (is_compressed_surface_format(format))
    {
        glCompressedTextureSubImage2D(_id, si_level, 0, 0, si_width, si_height, si_format, data.size(), data.data());
    }
    else
    {
        glTextureSubImage2D(_id, si_level, 0, 0, si_width, si_height, si_format, GL_UNSIGNED_BYTE, data.data());
    }
}

void TextureStorage::create() noexcept
{
    glCreateTextures(static_cast<GLenum>(_target), 1, &_id);

    Ensures(_id > 0);
}

}}}
