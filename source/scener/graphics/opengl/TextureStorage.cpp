// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "scener/graphics/opengl/TextureStorage.hpp"

#include "scener/graphics/SurfaceFormat.hpp"

namespace scener { namespace graphics { namespace opengl {

texture_storage::texture_storage(texture_target target) noexcept
    : _id     { 0 }
    , _target { target }
{
    create();
}

texture_storage::~texture_storage() noexcept
{
    if (_id != 0)
    {
        glDeleteTextures(1, &_id);
        _id = 0;
    }
}

std::uint32_t texture_storage::id() const noexcept
{
    return _id;
}

void texture_storage::bind() const noexcept
{
    glBindTextureUnit(0, _id);
}

void texture_storage::unbind() const noexcept
{
    glBindTextureUnit(0, 0);
}

void texture_storage::declare_storage(surface_format format
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

void texture_storage::set_data(surface_format                        format
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

void texture_storage::create() noexcept
{
    glCreateTextures(static_cast<GLenum>(_target), 1, &_id);

    Ensures(_id > 0);
}

}}}
