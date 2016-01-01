// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_IEFFECTLIGHTS_HPP
#define SCENER_GRAPHICS_IEFFECTLIGHTS_HPP

namespace SceneR { namespace Math { struct Vector3; } }

namespace SceneR { namespace Graphics {

class DirectionalLight;

/**
 * Defines the lighting parameters for the current effect.
 * A basic effect implements per-vertex lighting using three directional lights.
 */
class IEffectLights
{
public:
    /**
     * Releases all resource sbeing used by this IEffectsLights instance
     */
    virtual ~IEffectLights() = default;

public:
    /**
     * Gets the ambient light for the current effect
     */
    virtual const SceneR::Math::Vector3& ambient_light_color() const noexcept = 0;

    /**
     * Gets the ambient light for the current effect
     */
    virtual void ambient_light_color(const SceneR::Math::Vector3& ambientLightColor) noexcept = 0;

    /**
     * Gets the first directional light
     */
    virtual const DirectionalLight& directional_light_0() const noexcept = 0;

    /**
     * Gets the second directional light
     */
    virtual const DirectionalLight& directional_light_1() const noexcept = 0;

    /**
     * Gets the third directional light
     */
    virtual const DirectionalLight& directional_light_2() const noexcept = 0;

    /**
     * Gets a value indicating wheter lighting is enabled for the current effect.
     */
    virtual bool lighting_enabled() const noexcept = 0;

    /**
     * Gets a value indicating wheter lighting is enabled for the current effect.
     */
    virtual void lighting_enabled(bool lightingEnabled) noexcept = 0;

    /**
     * Enables default lighting for the current effect.
     * http://xboxforums.create.msdn.com/forums/t/25547.aspx
     * http://blogs.msdn.com/b/shawnhar/archive/2007/04/09/the-standard-lighting-rig.aspx
     */
    virtual void enable_default_lighting() noexcept = 0;
};

}}

#endif // SCENER_GRAPHICS_IEFFECTLIGHTS_HPP
