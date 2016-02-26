// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_OPENGL_TEXTUREOBJECT_HPP
#define SCENER_GRAPHICS_OPENGL_TEXTUREOBJECT_HPP

#include <cstddef>
#include <cstdint>

#include <gsl.h>

#include "scener/graphics/SurfaceFormat.hpp"
#include "scener/graphics/opengl/TextureTarget.hpp"

namespace scener { namespace graphics { namespace opengl {

/// Represents an opengl texture object.
class TextureStorage final
{
private:
    constexpr static bool is_compressed_surface_format(scener::graphics::surface_format format) noexcept
    {
        return (format == surface_format::dxt1 || format == surface_format::dxt3 || format == surface_format::dxt5);
    }

public:
    /// Initializes a new instance of the TextureStorage class.
    /// \param target the texturer target.
    TextureStorage(texture_target target) noexcept;

    /// Releases all resources being used by this TextureStorage.
    ~TextureStorage() noexcept;

public:
    /// Gets the texture object identifier
    std::uint32_t id() const noexcept;

    /// Binds the texture object.
    void bind() const noexcept;

    /// Unbinds the texture object.
    void unbind() const noexcept;

    /// Declares the texture storage parameters.
    /// \param format the format of the texture data.
    /// \param levels the texture mimap count.
    /// \param width the texture width.
    /// \param height the texture height.
    void declare_storage(scener::graphics::surface_format format
                       , std::size_t                     levels
                       , std::size_t                     width
                       , std::size_t                     height) const noexcept;

    /// Adds texture data to the texture object.
    /// \param format the format of the mipmap data.
    /// \param level the mipmap level index.
    /// \param width the mipmap width.
    /// \param height the mipmap height.
    /// \param data the mipmap data.
    void set_data(scener::graphics::surface_format      format
                , std::size_t                          level
                , std::size_t                          width
                , std::size_t                          height
                , const gsl::span<const std::uint8_t>& data) const noexcept;

private:
    void create() noexcept;

private:
    TextureStorage(const TextureStorage&) = delete;
    TextureStorage& operator=(const TextureStorage&) = delete;

private:
    std::uint32_t _id;
    texture_target _target;
};

}}}

#endif // SCENER_GRAPHICS_OPENGL_TEXTUREOBJECT_HPP
