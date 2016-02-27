// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_TEXTURE2D_HPP
#define SCENER_GRAPHICS_TEXTURE2D_HPP

#include <cstddef>
#include <cstdint>
#include <memory>

#include <gsl.h>

#include "scener/graphics/SurfaceFormat.hpp"
#include "scener/graphics/Texture.hpp"
#include "scener/graphics/opengl/TextureStorage.hpp"

namespace scener { namespace content { namespace readers { template <typename T> class content_type_reader; } } }

namespace scener { namespace graphics {

class graphics_device;
class sampler_state;

/// Represents a 2D texture.
class texture2d final : public texture
{
public:
    /// Creates a new instance of the Texture2D class.
    /// \param device the graphics device associated with this texture.
    /// \param width the texture width, in pixels
    /// \param height the texture height, in pixels
    texture2d(gsl::not_null<graphics_device*> device, std::size_t width, std::size_t height) noexcept;

    /// Creates a new instance of the Texture2D class.
    /// \param device the graphics device associated with this texture.
    /// \param width the texture width, in pixels
    /// \param height the texture height, in pixels
    /// \param format texture data format
    texture2d(gsl::not_null<graphics_device*> device
            , std::size_t                     width
            , std::size_t                     height
            , surface_format                  format) noexcept;

    /// Releases all resources being used by this texture.
    ~texture2d() override = default;

public:
    /// Gets the texture identifier.
    /// \returns the texture identifier.
    std::uint32_t id() const noexcept override;

    /// Gets the format of the texture data.
    /// \returns the format of the texture data.
    surface_format format() const noexcept override;

    /// Gets the texture height, in pixels.
    /// \returns the texture height, in pixels.
    std::size_t height() const noexcept;

    /// Gets the number of texture levels in a multilevel texture.
    /// \returns the number of texture levels in a multilevel texture.
    std::size_t level_count() const noexcept override;

    /// Gets the texture width, in pixels.
    /// \returns the texture width, in pixels.
    std::size_t width() const noexcept;

    /// Gets the texure sampler state.
    /// \returns the texure sampler state.
    graphics::sampler_state* sampler_state() const noexcept;

    /// Sets mipmap data to the texture.
    /// \param level the mipmap level.
    /// \param width the mipmap width, in pixels.
    /// \param height the mipmap height, in pixels.
    /// \param data pointer with the mipmap data.
    void set_data(std::size_t                          level
                , std::size_t                          width
                , std::size_t                          height
                , const gsl::span<const std::uint8_t>& data) const noexcept;

    /// Activates the texture object.
    void bind() const noexcept override;

    ///  Deactivates the texture object.
    void unbind() const noexcept override;

private:
    void declare_storage(std::size_t mipMapLevels) noexcept;

private:
    surface_format                           _format;
    std::size_t                              _mipmap_levels;
    std::size_t                              _height;
    std::size_t                              _width;
    std::shared_ptr<graphics::sampler_state> _sampler_state;
    opengl::texture_storage                  _storage;

    template <typename T> friend class scener::content::readers::content_type_reader;
};

}}

#endif // SCENER_GRAPHICS_TEXTURE2D_HPP
