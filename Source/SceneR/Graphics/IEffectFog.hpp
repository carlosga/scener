// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_GRAPHICS_IEFFECTFOG_HPP
#define SCENER_GRAPHICS_IEFFECTFOG_HPP

namespace SceneR { namespace Math { struct Vector3; } }

namespace SceneR { namespace Graphics {

/**
 * Defines fog parameters for the current effect.
 */
class IEffectFog
{
public:
    /**
     * Releases all resource sbeing used by this IEffectFog instance
     */
    virtual ~IEffectFog() = default;

public:
    /**
     *  Gets the fog color.
     */
    virtual const SceneR::Math::Vector3& fog_color() const noexcept = 0;

    /**
     *  Set the fog color.
     */
    virtual void fog_color(const SceneR::Math::Vector3& color) noexcept = 0;

    /**
     * Gets a value indicating whether for is enabled for the current effect.
     */
    virtual bool fog_enabled() const noexcept = 0;

    /**
     * Gets a value indicating whether for is enabled for the current effect.
     */
    virtual void fog_enabled(bool fogEnabled) noexcept = 0;

    /**
     * Gets maximum z value for fog.
     */
    virtual float fog_end() const noexcept = 0;

    /**
     * Sets maximum z value for fog.
     */
    virtual void fog_end(float fogEnd) noexcept = 0;

    /**
     * Gets minimum z value for fog.
     */
    virtual float fog_start() const noexcept = 0;

    /**
     * Sets minimum z value for fog.
     */
    virtual void fog_start(float fogStart) noexcept = 0;
};

}}

#endif // SCENER_GRAPHICS_IEFFECTFOG_HPP
