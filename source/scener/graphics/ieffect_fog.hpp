// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_IEFFECT_FOG_HPP
#define SCENER_GRAPHICS_IEFFECT_FOG_HPP

#include "scener/math/basic_vector.hpp"

namespace scener::graphics
{
    /// Defines fog parameters for the current effect.
    class ieffect_fog
    {
    public:
        /// Releases all resource sbeing used by this IEffectFog instance
        virtual ~ieffect_fog() = default;

    public:
        /// Gets the fog color as a three component color.
        /// \returns the fog color as a three component color.
        virtual const scener::math::vector3& fog_color() const noexcept = 0;

        /// Set the fog color as a three component color.
        /// \param color the fog color as a three component color.
        virtual void fog_color(const scener::math::vector3& color) noexcept = 0;

        /// Gets a value indicating whether for is enabled for the current effect.
        /// \returns true if the fog is enabled; false otherwise.
        virtual bool fog_enabled() const noexcept = 0;

        /// Gets a value indicating whether for is enabled for the current effect.
        /// \param fogEnabled true to enable fog, false otherwise.
        virtual void fog_enabled(bool fogEnabled) noexcept = 0;

        /// Gets maximum z value for fog.
        /// \returns the distance from the camera to stop adding fog, in world space.
        virtual float fog_end() const noexcept = 0;

        /// Sets maximum z value for fog.
        /// \param fogEnd the distance from the camera to stop adding fog, in world space.
        virtual void fog_end(float fog_end) noexcept = 0;

        /// Gets minimum z value for fog.
        /// \returns the distance from the camera to begin adding fog, in world space.
        virtual float fog_start() const noexcept = 0;

        /// Sets minimum z value for fog.
        /// \param forStart the distance from the camera to begin adding fog, in world space.
        virtual void fog_start(float fog_start) noexcept = 0;
    };
}

#endif // SCENER_GRAPHICS_IEFFECT_FOG_HPP
