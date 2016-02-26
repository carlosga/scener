// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_IEFFECTLIGHTS_HPP
#define SCENER_GRAPHICS_IEFFECTLIGHTS_HPP

#include "scener/math/basic_vector.hpp"

namespace scener { namespace graphics {

class directional_light;

/// Defines the lighting parameters for the current effect.
/// A basic effect implements per-vertex lighting using three directional lights.
class ieffect_lights
{
public:
    /// Releases all resource sbeing used by this IEffectsLights instance
    virtual ~ieffect_lights() = default;

public:
    /// Gets the ambient light for the current effect.
    /// \returns the ambient light for the current effect as a three component color.
    virtual const scener::math::vector3& ambient_light_color() const noexcept = 0;

    /// Sets the ambient light for the current effect.
    /// \param ambientLightColor the ambient light for the current effect as a three component color.
    virtual void ambient_light_color(const scener::math::vector3& ambientLightColor) noexcept = 0;

    /// Gets the first directional light.
    /// \returns the directional light.
    virtual const directional_light& directional_light_0() const noexcept = 0;

    /// Gets the second directional light.
    /// \returns the directional light.
    virtual const directional_light& directional_light_1() const noexcept = 0;

    /// Gets the third directional light.
    /// \returns the directional light.
    virtual const directional_light& directional_light_2() const noexcept = 0;

    /// Gets a value indicating wheter lighting is enabled for the current effect.
    /// \returns true if lighting is enabled; false otherwise.
    virtual bool lighting_enabled() const noexcept = 0;

    /// Gets a value indicating wheter lighting is enabled for the current effect.
    /// \param lightingEnabled true to enable lighting; false otherwise.
    virtual void lighting_enabled(bool lightingEnabled) noexcept = 0;

    /// Enables default lighting for the current effect.
    /// http://xboxforums.create.msdn.com/forums/t/25547.aspx
    /// http://blogs.msdn.com/b/shawnhar/archive/2007/04/09/the-standard-lighting-rig.aspx
    virtual void enable_default_lighting() noexcept = 0;
};

}}

#endif // SCENER_GRAPHICS_IEFFECTLIGHTS_HPP
