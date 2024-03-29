// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_TEXTURE2D_HPP
#define SCENER_GRAPHICS_TEXTURE2D_HPP

#include <cstddef>
#include <cstdint>
#include <memory>

#include <gsl/gsl>
#include <vulkan/vulkan.hpp>

#include "scener/graphics/surface_format.hpp"
#include "scener/graphics/texture.hpp"
#include "scener/graphics/vulkan/texture_object.hpp"

namespace scener::content::readers { template <typename T> class content_type_reader; }

namespace scener::graphics
{
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
        texture2d(gsl::not_null<graphics_device*> device, std::uint32_t width, std::uint32_t height) noexcept;

        /// Creates a new instance of the Texture2D class.
        /// \param device the graphics device associated with this texture.
        /// \param width the texture width, in pixels
        /// \param height the texture height, in pixels
        /// \param format texture data format
        texture2d(gsl::not_null<graphics_device*> device
                , std::uint32_t                   width
                , std::uint32_t                   height
                , surface_format                  format) noexcept;

        ~texture2d() override;

    public:
        /// Gets the texture identifier.
        /// \returns the texture identifier.
        std::uint32_t id() const noexcept override;

        /// Gets the format of the texture data.
        /// \returns the format of the texture data.
        surface_format format() const noexcept override;

        /// Gets the number of texture levels in a multilevel texture.
        /// \returns the number of texture levels in a multilevel texture.
        std::uint32_t level_count() const noexcept override;

        /// Gets the texture width, in pixels.
        /// \returns the texture width, in pixels.
        std::uint32_t width() const noexcept;

        /// Gets the texture height, in pixels.
        /// \returns the texture height, in pixels.
        std::uint32_t height() const noexcept;

        const vk::Sampler& sampler() const noexcept override;
        const vk::ImageView& view() const noexcept override;

    private:
        surface_format         _format;
        std::uint32_t          _mipmap_levels;
        std::uint32_t          _height;
        std::uint32_t          _width;
        vulkan::texture_object _texture_object;

        template <typename T> friend class scener::content::readers::content_type_reader;
    };
}

#endif // SCENER_GRAPHICS_TEXTURE2D_HPP
