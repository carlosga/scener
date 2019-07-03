// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_TEXTURE_HPP
#define SCENER_GRAPHICS_TEXTURE_HPP

#include <cstddef>
#include <cstdint>

#include "scener/graphics/graphics_resource.hpp"

namespace scener::graphics
{
    enum class surface_format : std::uint32_t;

    class graphics_device;

    /// Represents a texture reference.
    class texture : public graphics_resource
    {
    public:
        /// Initializes a new instance of the Texture class.
        /// \param device the GraphicsDevice associated with this RasterizerState.
        texture(gsl::not_null<graphics_device*> device) noexcept;

        /// Releases all resources being used by this texture.
        ~texture() override = default;

    public:
        /// Gets the texture identifier.
        /// \returns the texture identifier.
        virtual std::uint32_t id() const noexcept = 0;

        /// Gets the format of the texture data.
        /// \returns the format of the texture data.
        virtual surface_format format() const noexcept = 0;

        /// Gets the number of texture levels in a multilevel texture.
        /// \returns the number of texture levels in a multilevel texture.
        virtual std::uint32_t level_count() const noexcept = 0;

        /// Activates the texture object.
        virtual void bind() const noexcept = 0;

        /// Deactivates the texture object.
        virtual void unbind() const noexcept = 0;
    };
}

#endif // SCENER_GRAPHICS_TEXTURE_HPP
